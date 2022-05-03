/****************************************************************************
 * Copyright (C) from 2009 to Present EPAM Systems.
 *
 * This file is part of Imago toolkit.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***************************************************************************/

#include "chemical_structure_recognizer.h"

#include <cmath>
#include <cstdio>
#include <deque>
#include <memory>

#include "approximator.h"
#include "chemical_structure_recognizer.h"
#include "graph_extractor.h"
#include "graphics_detector.h"
#include "image.h"
#include "image_utils.h"
#include "label_combiner.h"
#include "label_logic.h"
#include "log_ext.h"
#include "molecule.h"
#include "pixel_boundings.h"
#include "platform_tools.h"
#include "prefilter_basic.h"
#include "segment.h"
#include "segmentator.h"
#include "separator.h"
#include "superatom.h"
#include "vec2d.h"
#include "weak_segmentator.h"
#include "wedge_bond_extractor.h"

using namespace imago;

ChemicalStructureRecognizer::ChemicalStructureRecognizer() : _cr()
{
}

double maxHeightHelper(const Settings& vars, int lines)
{
    double maxHeight = (vars.lab_remover.HeightFactor * vars.dynamic.CapitalHeight + (lines - 1) * vars.dynamic.CapitalHeight) * vars.separator.capHeightMax;
    return maxHeight;
}

bool ChemicalStructureRecognizer::removeMoleculeCaptions(const Settings& vars, Image& img, SegmentDeque& symbols, SegmentDeque& graphics)
{
    logEnterFunction();

    bool result = false;

    getLogExt().append("Symbols height", vars.dynamic.CapitalHeight);

    if (vars.dynamic.CapitalHeight < vars.lab_remover.MinCapitalHeight || vars.dynamic.CapitalHeight > vars.lab_remover.MaxCapitalHeight)
    {
        getLogExt().appendText("Unappropriate symbols height");
        return result;
    }

    getLogExt().append("Symbols height max", vars.separator.capHeightMax);
    getLogExt().appendImage("img", img);

    const int min_cap_chars = vars.lab_remover.MinLabelChars;
    double minWidth =
        min_cap_chars * (vars.estimation.MinSymRatio + vars.estimation.MaxSymRatio) / 2.0 * vars.dynamic.CapitalHeight * vars.estimation.CapitalHeightError;
    double maxHeight = maxHeightHelper(vars, vars.lab_remover.MaxLabelLines);
    double minHeight = vars.dynamic.CapitalHeight * vars.separator.capHeightMin;
    double centerShiftMax = vars.lab_remover.CenterShiftMax;
    int borderDistance = round(vars.dynamic.CapitalHeight);
    getLogExt().append("minWidth", minWidth);
    getLogExt().append("maxHeight", maxHeight);
    getLogExt().append("minHeight", minHeight);
    getLogExt().append("borderDistance", borderDistance);

    WeakSegmentator ws(img.getWidth(), img.getHeight());
    ws.appendData(img, WeakSegmentator::getLookupPattern((int)vars.dynamic.CapitalHeight, false));

    if (ws.SegmentPoints.size() < 2)
    {
        getLogExt().appendText("Only one segment, ignoring");
        return result;
    }

    for (WeakSegmentator::SegMap::iterator it = ws.SegmentPoints.begin(); it != ws.SegmentPoints.end(); ++it)
    {
        RectShapedBounding b(it->second);
        const Rectangle& bounding = b.getBounding();
        getLogExt().appendPoints("segment", it->second);
        getLogExt().append("width", bounding.width);
        getLogExt().append("height", bounding.height);
        if (bounding.height <= maxHeight && bounding.height >= minHeight && bounding.width >= minWidth &&
            (bounding.y1() < borderDistance || bounding.y2() >= img.getHeight() - borderDistance) &&
            (bounding.x1() < borderDistance || bounding.x2() >= img.getWidth() - borderDistance ||
             absolute((bounding.x1() + bounding.x2()) / 2.0 - img.getWidth() / 2.0) <= centerShiftMax * borderDistance))
        {
            getLogExt().appendPoints("possibly caption", it->second);

            {
                Rectangle badBounding = b.getBounding();
                double value = 0.0;
                int count = 0;
                for (int x = badBounding.x1(); x <= badBounding.x2() && x < img.getWidth(); x++)
                {
                    for (int y = badBounding.y1(); y <= badBounding.y2() && y < img.getHeight(); y++)
                    {
                        if (img.getByte(x, y) == 0)
                            value += 1.0;
                        count++;
                    }
                }
                value /= count;
                getLogExt().append("Average density", value);

                if (value > vars.lab_remover.MinimalDensity)
                {
                    getLogExt().appendText("Caption bounding is found, filtering segments");

                    std::vector<Segment*> bad_symbols;
                    std::vector<Segment*> bad_graphics;

                    for (SegmentDeque::iterator it = symbols.begin(); it != symbols.end(); ++it)
                        if ((*it)->getX() >= badBounding.x1() - vars.lab_remover.PixGapX && (*it)->getX() < badBounding.x2() &&
                            (*it)->getY() >= badBounding.y1() - vars.lab_remover.PixGapY &&
                            (*it)->getY() + (*it)->getHeight() <= badBounding.y2() + vars.lab_remover.PixGapY)
                        {
                            bad_symbols.push_back(*it);
                        }

                    for (SegmentDeque::iterator it = graphics.begin(); it != graphics.end(); ++it)
                        if ((*it)->getX() >= badBounding.x1() - vars.lab_remover.PixGapX && (*it)->getX() < badBounding.x2() &&
                            (*it)->getY() >= badBounding.y1() - vars.lab_remover.PixGapY &&
                            (*it)->getY() + (*it)->getHeight() <= badBounding.y2() + vars.lab_remover.PixGapY)
                        {
                            bad_graphics.push_back(*it);
                        }

                    if (bad_symbols.size() >= bad_graphics.size())
                    {
                        getLogExt().appendText("Clearing the image");
                        for (int x = badBounding.x1(); x <= badBounding.x2() && x < img.getWidth(); x++)
                            for (int y = badBounding.y1(); y <= badBounding.y2() && y < img.getHeight(); y++)
                                img.getByte(x, y) = 255;

                        result = true;
                    } // if letters>graphics

                } // if density
            }     // locals
        }         // if bounding passes size constraints
    }             // for

    return result;
}

void ChemicalStructureRecognizer::segmentate(const Settings& vars, Image& img, SegmentDeque& segments, bool reconnect)
{
    logEnterFunction();

    // extract segments using WeakSegmentator
    WeakSegmentator ws(img.getWidth(), img.getHeight());
    ws.appendData(img, WeakSegmentator::getLookupPattern(vars.csr.WeakSegmentatorDist), reconnect);
    for (WeakSegmentator::SegMap::iterator it = ws.SegmentPoints.begin(); it != ws.SegmentPoints.end(); ++it)
    {
        const Points2i& pts = it->second;
        RectShapedBounding b(pts);
        Segment* s = new Segment();
        s->init(b.getBounding().width + 1, b.getBounding().height + 1);
        s->fillWhite();
        s->getX() = b.getBounding().x;
        s->getY() = b.getBounding().y;
        for (size_t u = 0; u < pts.size(); u++)
            s->getByte(pts[u].x - b.getBounding().x, pts[u].y - b.getBounding().y) = 0;
        segments.push_back(s);
    }
}

void ChemicalStructureRecognizer::storeSegments(const Settings& vars, SegmentDeque& layer_symbols, SegmentDeque& layer_graphics)
{
    logEnterFunction();

    for (Segment* s : layer_symbols)
    {
        RecognitionDistance rd = getCharacterRecognizer().recognize(vars, *s, CharacterRecognizer::all);
        double dist = 0.0;
        char res = rd.getBest(&dist);
        double qual = rd.getQuality();

        char filename[MAX_TEXT_LINE] = {0};

        platform::MKDIR("./characters");

        if (dist > vars.characters.PossibleCharacterDistanceWeak)
        {
            int digits = (int)std::log10(dist);
            if (digits > 10)
                dist /= std::pow(10.0, digits - 10);
            // in case res == 0 is true filename does not get the name of the file and exception is thrown
            if (res == 0)
                res = '0';
            platform::MKDIR("./characters/bad");
            sprintf(filename, "./characters/bad/%c_d%4.2f_q%4.2f.png", res, dist, qual);
        }
        else if (qual < vars.characters.PossibleCharacterMinimalQuality)
        {
            platform::MKDIR("./characters/similar");
            sprintf(filename, "./characters/similar/%c_d%4.2f_q%4.2f.png", res, dist, qual);
        }
        else
        {
            platform::MKDIR("./characters/good");
            sprintf(filename, "./characters/good/%c_d%4.2f_q%4.2f.png", res, dist, qual);
        }

        ImageUtils::saveImageToFile(*s, filename);
    }

    for (Segment* s : layer_graphics)
    {
        char filename[MAX_TEXT_LINE] = {0};
        platform::MKDIR("./graphics");
        sprintf(filename, "./graphics/d%4.2f_q%4.2f.png", s->density(), s->getRatio());
        ImageUtils::saveImageToFile(*s, filename);
    }
}

/*
bool ChemicalStructureRecognizer::isReconnectSegmentsRequired(const Settings& vars, const Image& img, const SegmentDeque& segments)
{
logEnterFunction();

if (img.getWidth() < vars.csr.SmallImageDim && img.getHeight() < vars.csr.SmallImageDim)
{
getLogExt().appendText("Too small image to analyze");
return false;
}

getLogExt().append("Segments count", segments.size());

double avg_fill = 0.0;
int surely_bad = 0;
int probably_bad = 0;
int probably_good = 0;
int surely_good = 0;

for (size_t u = 0; u < segments.size(); u++)
{
size_t count = SegmentTools::getAllFilled((*segments[u])).size();
avg_fill += count;
if (count < vars.prefilterCV.MinGoodPixelsCount / 2)
surely_bad++;
else if (count < vars.prefilterCV.MinGoodPixelsCount)
probably_bad++;
else if (count > vars.prefilterCV.MinGoodPixelsCount * 2)
surely_good++;
else
probably_good++;
}
avg_fill /= segments.size();

getLogExt().append("Average fill", avg_fill);
getLogExt().append("Surely bad", surely_bad);
getLogExt().append("Probably bad", probably_bad);
getLogExt().append("Probably good", probably_good);
getLogExt().append("Surely good", surely_good);

bool result = (surely_bad > vars.csr.ReconnectMinBads) &&
(vars.csr.ReconnectSurelyBadCoef * surely_bad >
vars.csr.ReconnectSurelyGoodCoef * surely_good +
vars.csr.ReconnectProbablyGoodCoef * probably_good );

return result;
}
*/

bool ChemicalStructureRecognizer::isReconnectSegmentsRequired(const Settings& vars, const Image& img, const SegmentDeque& segments)
{
    logEnterFunction();

    if (img.getWidth() < vars.csr.SmallImageDim && img.getHeight() < vars.csr.SmallImageDim)
    {
        getLogExt().appendText("Too small image to analyze");
        return false;
    }

    getLogExt().append("Segments count", segments.size());

    double avg_fill = 0.0;
    double avg_diam = 0.0;
    int too_small = 0;
    int too_light = 0;

    for (size_t u = 0; u < segments.size(); u++)
    {
        size_t count = SegmentTools::getAllFilled((*segments[u])).size();
        avg_fill += count;
        double d = segments[u]->getDiameter();
        avg_diam += d;

        //        getLogExt().append("Segment fill count", count);
        //        getLogExt().append("Segment diameter", d);
    }
    //	avg_fill /= segments.size();
    avg_diam /= segments.size();

    //	getLogExt().append("Average fill", avg_fill);
    getLogExt().append("Average diameter", avg_diam);

    for (size_t u = 0; u < segments.size(); u++)
    {
        size_t count = SegmentTools::getAllFilled((*segments[u])).size();
        if (count < avg_fill)
            too_light++;
        double d = segments[u]->getDiameter();
        if (d < (avg_diam / 3.0))
            too_small++;
    }

    getLogExt().append("Too small segments", too_small);
    //	getLogExt().append("Too light segments", too_light);

    bool result = (too_small > segments.size() / 5);

    return result;
}

void ClearSegments(SegmentDeque& segs, SegmentDeque& segSymbols, SegmentDeque& segGraphics)
{
    std::map<std::string, Segment*> all_segs;
    std::map<std::string, Segment*>::iterator map_it;
    SegmentDeque::iterator it;

    for (it = segs.begin(); it != segs.end(); ++it)
    {
        std::ostringstream str;
        str << (*it);
        all_segs[str.str()] = (*it);
    }

    for (it = segSymbols.begin(); it != segSymbols.end(); ++it)
    {
        std::ostringstream str;
        str << (*it);
        if (all_segs.find(str.str()) == all_segs.end())
            all_segs[str.str()] = (*it);
    }

    for (it = segGraphics.begin(); it != segGraphics.end(); ++it)
    {
        std::ostringstream str;
        str << (*it);
        if (all_segs.find(str.str()) == all_segs.end())
            all_segs[str.str()] = (*it);
    }

    for (map_it = all_segs.begin(); map_it != all_segs.end(); ++map_it)
    {
        if ((*map_it).second)
            delete (*map_it).second;
    }

    segGraphics.clear();
    segSymbols.clear();
    segs.clear();
    all_segs.clear();
}
void ChemicalStructureRecognizer::recognize_new(Settings& vars, Molecule& mol)
{
    /*
    1. weak binarization, segmentate
    2. extractGraphics (weak binarization)
    3. estimateBondLen (weak binarization)
    4. searching optimal strong binarization for symbols and singleDownFetch
    5. strong binarization
    6. singleDownFetch(estimateedBondLen, strong binarization)
    7. avoiding "single down" bonds from weak binarization
    8. avoiding "single down" bonds from strong binarization
    9. segmentate strong binarization
    10. searching symbol segments in strong binarization
    11. separateStokedSymbols
    12. repareBrokenSymbols
    13. avoiding symbols from weak binarization
    14. segmentate weak binarization, build skeleton
    15. lineCombiner
    16. mapping
    */
}

void ChemicalStructureRecognizer::recognize(Settings& vars, Molecule& mol)
{
    logEnterFunction();

    Image& _copyImg = _origImage;

    bool captions_removed = false;

    {
        SegmentDeque segments;
        SegmentDeque layer_symbols, layer_graphics, layer_lines;

        try
        {
            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            mol.clear();

            getLogExt().appendImage("Original image", _origImage);

            Image graphics;
            graphics.copy(_origImage);

            //                                vars.prefilterCV.WeakBinarizeSize = 1;
            //                                vars.prefilterCV.WeakBinarizeTresh = 5.0;
            vars.prefilterCV.WeakBinarizeSize = 25;
            vars.prefilterCV.WeakBinarizeTresh = 5.0;

            //     				prefilter_basic::prefilterBasicForceDownscale(vars, graphics);

            getLogExt().appendText("Binarize image for graphics");
            getLogExt().append("Strong Binarize Size", vars.prefilterCV.StrongBinarizeSize);
            getLogExt().append("Strong Binarize Tresh", vars.prefilterCV.StrongBinarizeTresh);
            getLogExt().append("Weak Binarize Size", vars.prefilterCV.WeakBinarizeSize);
            getLogExt().append("Weak Binarize Tresh", vars.prefilterCV.WeakBinarizeTresh);

            prefilter_basic::prefilterBasicFullsize(vars, graphics);
            //            prefilter_retinex::prefilterRetinexFullsize(vars, graphics);

            double roughness = graphics.getRoughness3();
            getLogExt().append("Roughness", roughness);

            segmentate(vars, graphics, segments);

            double bad_estimated_bond_len = graphics.estimateBondLen(segments);
            ImageUtils::extractGraphics(graphics, segments, layer_graphics, layer_symbols, layer_lines, bad_estimated_bond_len);

            double estimated_bond_len;
            if (layer_graphics.size() > 0)
                estimated_bond_len = graphics.estimateBondLen(layer_graphics);
            else if (layer_lines.size() > 0)
                estimated_bond_len = graphics.estimateBondLen(layer_lines);
            else if (layer_symbols.size() > 0)
                estimated_bond_len = graphics.estimateBondLen(layer_symbols);

            vars.dynamic.LineThickness = ImageUtils::estimateLineThickness(graphics, vars.routines.LineThick_Grid);

            Image _img;
            _img.copy(_origImage);

            //            vars.prefilterCV.WeakBinarizeSize = vars.dynamic.LineThickness/2.0 + 1.0;
            vars.prefilterCV.WeakBinarizeSize = vars.prefilterCV.StrongBinarizeSize;
            vars.prefilterCV.WeakBinarizeTresh = vars.prefilterCV.StrongBinarizeTresh;

            getLogExt().appendText("Binarize image for Bonds Down");
            getLogExt().append("Strong Binarize Size", vars.prefilterCV.StrongBinarizeSize);
            getLogExt().append("Strong Binarize Tresh", vars.prefilterCV.StrongBinarizeTresh);
            getLogExt().append("Weak Binarize Size", vars.prefilterCV.WeakBinarizeSize);
            getLogExt().append("Weak Binarize Tresh", vars.prefilterCV.WeakBinarizeTresh);

            prefilter_basic::prefilterBasicFullsize(vars, _img);
            //            prefilter_retinex::prefilterRetinexFullsize(vars, _img);

            roughness = _img.getRoughness3();
            getLogExt().append("Initial Roughness (After strong binarization)", roughness);

            if (roughness > 0.01)
            {
                getLogExt().appendText("Looks like low quality image, use garphics image for down bonds analysis.");
                _img = graphics;
            }
            //			prefilter_basic::prefilterBasicForceDownscale(vars, _img);

            //			_img.crop();
            vars.general.ImageWidth = _img.getWidth();
            vars.general.ImageHeight = _img.getHeight();

            if (!_img.isInit())
            {
                throw ImagoException("Empty image, nothing to recognize");
            }

            for (Segment* s : layer_symbols)
            {
                ImageUtils::cutSegmentExtra(_img, *s, 255);
            }

            /*
                        for (Segment *s : layer_graphics)
                        {
                            ImageUtils::cutSegmentExtra(_img, *s, 255);
                        }
            */
            segments.clear();
            segmentate(vars, _img, segments);

            WedgeBondExtractor wbe(segments, _img);
            SegmentDeque sdb_segs;
            sdb_segs.clear();
            {
                getLogExt().append("estimated_bond_len", estimated_bond_len);

                int sdb_count = wbe.singleDownFetch(vars, mol, sdb_segs, estimated_bond_len);
                //				int sdb_count = wbe.singleDownFetchOld(vars, mol, sdb_segs);
                getLogExt().append("Single-down bonds found", sdb_count);
            }

            /*ImageUtils::removeSegmentsFromDeque(layer_lines, sdb_segs);
            for (auto seg : layer_lines)
                if (seg->getDiameter() > 0.7 * estimated_bond_len) layer_graphics.push_back(seg);
                else layer_symbols.push_back(seg);*/

            //			bool reconnect = isReconnectSegmentsRequired(vars, _img, segments);

            for (auto seg : layer_lines)
            {
                if (seg->getDiameter() > 0.7 * estimated_bond_len)
                    layer_graphics.push_back(seg);
                else
                    layer_symbols.push_back(seg);
            }

            Image symbols;
            symbols.copy(_origImage);

            vars.prefilterCV.WeakBinarizeSize = vars.dynamic.LineThickness / 2.0 + 1.0;
            vars.prefilterCV.WeakBinarizeTresh = 2.0;

            getLogExt().appendText("Binarize image for Symbols");
            getLogExt().append("Strong Binarize Size", vars.prefilterCV.StrongBinarizeSize);
            getLogExt().append("Strong Binarize Tresh", vars.prefilterCV.StrongBinarizeTresh);
            getLogExt().append("Weak Binarize Size", vars.prefilterCV.WeakBinarizeSize);
            getLogExt().append("Weak Binarize Tresh", vars.prefilterCV.WeakBinarizeTresh);

            prefilter_basic::prefilterBasicFullsize(vars, symbols);

            segments.clear();
            segmentate(vars, symbols, segments);

            roughness = symbols.getRoughness3();
            getLogExt().append("Roughness", roughness);

            double coef = _img.getWidth() / 2000.0;
            double need_roughness = 0.005 / coef;

            getLogExt().append("Needed roughness", need_roughness);

            while (isReconnectSegmentsRequired(vars, symbols, segments) || symbols.getRoughness3() > need_roughness)
            {
                // use filter
                Image temp_img;
                temp_img.copy(_origImage);

                vars.prefilterCV.WeakBinarizeSize = vars.prefilterCV.WeakBinarizeSize * 2;
                vars.prefilterCV.WeakBinarizeTresh = vars.prefilterCV.WeakBinarizeTresh + 1.0;
                if (vars.prefilterCV.WeakBinarizeSize > 30)
                    break;

                getLogExt().appendText("Binarize image for Symbols");
                getLogExt().append("Strong Binarize Size", vars.prefilterCV.StrongBinarizeSize);
                getLogExt().append("Strong Binarize Tresh", vars.prefilterCV.StrongBinarizeTresh);
                getLogExt().append("Weak Binarize Size", vars.prefilterCV.WeakBinarizeSize);
                getLogExt().append("Weak Binarize Tresh", vars.prefilterCV.WeakBinarizeTresh);

                prefilter_basic::prefilterBasicFullsize(vars, temp_img);
                //                prefilter_retinex::prefilterRetinexFullsize(vars, temp_img);

                SegmentDeque temp;
                segmentate(vars, temp_img, temp);

                if (temp.size() > 0)
                {
                    SegmentDeque temp1, temp2;
                    ClearSegments(segments, temp1, temp2);

                    segments = temp;
                    symbols.copy(temp_img);
                }

                getLogExt().appendImage("Reconnected image", symbols);

                roughness = symbols.getRoughness3();
                getLogExt().append("Roughness", roughness);
                if (roughness < need_roughness)
                    break;
            }

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            if (segments.size() == 0)
            {
                throw ImagoException("Empty image, nothing to recognize");
            }

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            ImageUtils::extractGraphics(symbols, segments, layer_graphics, layer_symbols, layer_lines, bad_estimated_bond_len);

            for (auto seg : layer_lines)
            {
                if (seg->getDiameter() > 0.7 * estimated_bond_len)
                    layer_graphics.push_back(seg);
                else
                    layer_symbols.push_back(seg);
            }

            for (Segment* s : sdb_segs)
            {
                ImageUtils::cutSegmentExtra(symbols, *s, 255);
            }

            for (Segment* s : layer_graphics)
            {
                ImageUtils::cutSegmentExtra(symbols, *s, 255);
            }

            int count_graphics = layer_graphics.size();

            getLogExt().appendImage("Image (for symbols extraction)", symbols);

            vars.dynamic.LineThickness = ImageUtils::estimateLineThickness(symbols, vars.routines.LineThick_Grid);

            ClearSegments(segments, layer_symbols, layer_graphics);

            segmentate(vars, symbols, segments);

            /*            ImageUtils::extractGraphics(symbols, segments, layer_graphics, layer_symbols, layer_lines, bad_estimated_bond_len);

                        for (auto seg : layer_lines)
                        {
                           layer_graphics.push_back(seg);
                        }
            */
            Separator sep(segments, symbols);

            sep.Separate(vars, _cr, layer_symbols, layer_graphics);

            /*
                        int guessedHeight = -1;
                        bool _heightRestricted = false;
                        guessedHeight = sep.estimateCapHeight(vars, _heightRestricted);
                        vars.dynamic.CapitalHeight = guessedHeight;

                        std::sort(layer_graphics.begin(), layer_graphics.end(), sep._segmentsComparator);
                        sep.SeparateStuckedSymbols(vars, layer_symbols, layer_graphics, _cr);
                        std::sort(layer_symbols.begin(), layer_symbols.end(), sep._segmentsComparator);
            */
            while (sep.RepairBrokenSymbols(vars, layer_symbols, layer_graphics, _cr))
            {
                getLogExt().append("Continue attempt repaire symbols", layer_symbols.size());
                std::sort(layer_symbols.begin(), layer_symbols.end(), sep._segmentsComparator);
            }

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            getLogExt().append("Symbols", layer_symbols.size());
            getLogExt().append("Graphics", layer_graphics.size());
            /*
                     if (vars.general.ImageAlreadyBinarized && !captions_removed)
                     {
                     if (removeMoleculeCaptions(vars, _origImage, layer_symbols, layer_graphics))
                     {
                     captions_removed = true;
                     getLogExt().appendText("Restart after molecule captions cleanup");
                     ClearSegments(segments, layer_symbols, layer_graphics);
                     // looks like performance degrade, but actually gives more accurate result (due to capital height re-estimation) at a almost zero-cost in
               terms of cpu time
                     }
                     }
                     */
            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            if (count_graphics == 0 && layer_symbols.size() == 1)
            {
                getLogExt().appendText("No graphics detected, assume symbols are graphics");
                layer_graphics = layer_symbols;
                layer_symbols.clear();
            }

            if (getLogExt().loggingEnabled())
            {
                Image symbols, graphics;

                symbols.emptyCopy(_img);
                graphics.emptyCopy(_img);

                for (Segment* s : layer_symbols)
                {
                    getLogExt().append("draw symbol", (void*)s);
                    ImageUtils::putSegment(symbols, *s, true);
                }

                for (Segment* s : layer_graphics)
                {
                    getLogExt().append("draw graphics", (void*)s);
                    ImageUtils::putSegment(graphics, *s, true);
                }

                getLogExt().appendImage("Letters", symbols);
                getLogExt().appendImage("Graphics", graphics);
            }

            if (vars.general.ExtractCharactersOnly)
            {
                storeSegments(vars, layer_symbols, layer_graphics);
                return;
            }

            if (!layer_symbols.empty())
            {
                if (vars.dynamic.CapitalHeight < 0.0)
                {
                    int sum_height = 0;
                    for (auto seg : layer_symbols)
                    {
                        sum_height += seg->getHeight();
                    }
                    vars.dynamic.CapitalHeight = sum_height / layer_symbols.size();
                }

                LabelCombiner lc(vars, layer_symbols, layer_graphics, _cr);

                if (vars.dynamic.CapitalHeight > 0.0)
                    lc.extractLabels(mol.getLabels());

                if (vars.checkTimeLimit())
                    throw ImagoException("Timelimit exceeded");

                if (getLogExt().loggingEnabled())
                {
                    Image symbols;
                    symbols.emptyCopy(_img);
                    for (Segment* s : layer_symbols)
                    {
                        ImageUtils::putSegment(symbols, *s, true);
                    }
                    getLogExt().appendImage("Symbols with layer_symbols added", symbols);
                }

                getLogExt().append("Found superatoms", mol.getLabels().size());
            }
            else
            {
                getLogExt().appendText("No symbols found");
            }

            Points2d ringCenters;

            getLogExt().appendText("Before line vectorization");

            //                                Image graphics;
            graphics.copy(_origImage);

            vars.prefilterCV.WeakBinarizeSize = 27;
            vars.prefilterCV.WeakBinarizeTresh = 5.0;

            prefilter_basic::prefilterBasicFullsize(vars, graphics);
            // prefilter_retinex::prefilterRetinexFullsize(vars, graphics);

            for (Segment* s : sdb_segs)
            {
                ImageUtils::cutSegmentExtra(graphics, *s, 255);
            }

            for (Segment* s : layer_symbols)
            {
                ImageUtils::cutSegmentExtra(graphics, *s, 255);
            }

            getLogExt().appendImage("Image (for graphics extraction)", graphics);

            vars.dynamic.LineThickness = ImageUtils::estimateLineThickness(graphics, vars.routines.LineThick_Grid);

            layer_graphics.clear();
            Segmentator::segmentate(graphics, layer_graphics);
            /*
                        ImageUtils::extractGraphics(graphics, segments, layer_graphics, layer_symbols, layer_lines, bad_estimated_bond_len);

                        for (auto seg : layer_lines)
                        {
                           if (seg->getDiameter() > 0.7 * estimated_bond_len)
                              layer_graphics.push_back(seg);
                        }
            */

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            {
                BaseApproximator* approximator = NULL;

                if (vars.csr.UseDPApproximator)
                    approximator = new DPApproximator();
                else
                    approximator = new CvApproximator();

                GraphicsDetector gd(approximator, vars.dynamic.LineThickness * vars.csr.LineVectorizationFactor);
                gd.extractRingsCenters(vars, layer_graphics, ringCenters);
                GraphExtractor::extract(vars, gd, layer_graphics, mol);

                delete approximator;
            }

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            while (mol._dissolveShortEdges(vars, vars.csr.Dissolve, true, layer_symbols))
            {
                if (vars.checkTimeLimit())
                    throw ImagoException("Timelimit exceeded");
            }

            getLogExt().appendSkeleton(vars, "after dissolve short edges", mol);

            while (mol._dissolveIntermediateVertices(vars))
            {
                if (vars.checkTimeLimit())
                    throw ImagoException("Timelimit exceeded");
            }

            getLogExt().appendSkeleton(vars, "after dissolve intermidiate vertices", mol);
            //            vars.dynamic.LineThickness = ImageUtils::estimateLineThickness(symbols, 1);
            WedgeBondExtractor wbe2(layer_graphics, graphics);
            wbe2.singleUpFetch(vars, mol);

            mol.deleteBadTriangles(vars.csr.DeleteBadTriangles);

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            if (!layer_symbols.empty())
            {
                LabelLogic ll(_cr);
                std::deque<Label> unmapped_labels;

                for (Label& l : mol.getLabels())
                {
                    if (vars.checkTimeLimit())
                        throw ImagoException("Timelimit exceeded");
                    ll.recognizeLabel(vars, l);
                }

                getLogExt().appendText("Label recognizing");

                mol.mapLabels(vars, unmapped_labels);

                getLogExt().append("Found unmapped labels", unmapped_labels.size());

                if (unmapped_labels.size() > 0)
                {
                    ll.checkUnmappedLabels(vars, unmapped_labels, mol.getLabels());
                    mol.updateLabels();
                }

                if (vars.checkTimeLimit())
                    throw ImagoException("Timelimit exceeded");

                GraphicsDetector().analyzeUnmappedLabels(unmapped_labels, ringCenters);
                getLogExt().append("Found rings", ringCenters.size());
            }
            else
            {
                getLogExt().appendText("Layer_symbols is empty!");
            }

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            mol.aromatize(ringCenters);

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            wbe.fixStereoCenters(mol);

            mol.calcShortBondsPenalty(vars);
            // mol.calcCloseVerticiesPenalty(vars);

            if (vars.checkTimeLimit())
                throw ImagoException("Timelimit exceeded");

            ClearSegments(segments, layer_symbols, layer_graphics);

            getLogExt().appendText("Recognition finished");
        }
        catch (ImagoException&)
        {
            ClearSegments(segments, layer_symbols, layer_graphics);
            throw;
        }
    }
}

void ChemicalStructureRecognizer::image2mol(Settings& vars, Image& img, Molecule& mol)
{
    logEnterFunction();
    setImage(img);
    recognize(vars, mol);
}

void ChemicalStructureRecognizer::extractCharacters(Settings& vars, Image& img)
{
    logEnterFunction();
    setImage(img);
    Molecule temp;
    // force-set characters extraction only:
    vars.general.ExtractCharactersOnly = true;
    recognize(vars, temp);
}

void ChemicalStructureRecognizer::setImage(Image& img)
{
    _origImage.copy(img);
}

ChemicalStructureRecognizer::~ChemicalStructureRecognizer()
{
}
