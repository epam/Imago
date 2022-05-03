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

#include "label_logic.h"

#include <cctype>
#include <cstring>

#include "character_recognizer.h"
#include "chemical_validity.h"
#include "image_utils.h"
#include "label_combiner.h"
#include "log_ext.h"
#include "periodic_table.h"
#include "segment.h"

using namespace imago;

const std::string exact_as_lower = "OSWVPZXCV";
const std::string can_not_be_capital = "XJUVWQ";
const std::string can_not_be_only_one_capital = "ADEGJLMQRTXZ";
const std::string can_not_be_in_comb[] = {"abdefhijknopqvwxyz",         "bcdfgjlmnopqstuvwxyz",       "bcghijknpqtvwxyz",           "acdefghijklmnopqrstuvwxz",
                                          "abcdefghijklmnopqtvwxyz",    "abcdfghijklnopqstuvwxyz",    "bcfghijklmnopqrstuvwxyz",    "abcdhijklmnpqrtuvwxyz",
                                          "abcdefghijklmopqstuvwxyz",   "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqstuvwxyz",  "bcdefghjklmnopqstvwxyz",
                                          "abcefhijklmpqrsuvwxyz",      "cfghjklmnqrstuvwxyz",        "abcdefghijklmnopqrtuvwxyz",  "cefghijklnpqsvwxyz",
                                          "abcdefghijklmnopqrstuvwxyz", "cdgijklmopqrstvwxyz",        "adfhjklopqstuvwxyz",         "dfgjknopqrstuvwxyz",
                                          "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdfghijklmnopqrstuvwxyz",
                                          "acdefghijklmnopqrstuvwxyz",  "abcdefghijklmopqstuvwxyz"};

std::string allowed_comb[26];

LabelLogic::LabelLogic(const CharacterRecognizer& cr) : _cr(cr), _satom(NULL), _cur_atom(NULL)
{
    //   _buildPossibleCombArray();
}

LabelLogic::~LabelLogic()
{
}

void LabelLogic::setSuperatom(Superatom* satom)
{
    _cur_atom = NULL;
    _satom = satom;
    _addAtom();
}

std::string substract(const std::string& fullset, const std::string& reduction)
{
    std::string result;
    for (std::string::const_iterator it = fullset.begin(); it != fullset.end(); ++it)
        if (reduction.find(*it) == std::string::npos)
            result += *it;
    return result;
}

void LabelLogic::process_ext(const Settings& vars, Segment* seg, int line_y)
{
    logEnterFunction();
    getLogExt().appendSegmentWithYLine(vars, "segment with baseline", *seg, line_y);

    bool possible_upperscript = false;
    bool possible_subscript = false;

    RecognitionDistance pr = _cr.recognize(vars, *seg);

    getLogExt().append("Ranged best candidates", pr.getRangedBest());

    {
        // adjust using image params
        if (line_y >= 0)
        {
            double underline = SegmentTools::getPercentageUnderLine(*seg, line_y);
            getLogExt().append("Percentage under baseline", underline);
            pr.adjust(1.0 - vars.labels.weightUnderline * (underline - vars.labels.underlinePos), CharacterRecognizer::digits);
        }

        getLogExt().append("Ranged best candidates", pr.getRangedBest());

        if ((vars.dynamic.CapitalHeight > 0) && (line_y > 0))
        {
            if ((line_y - seg->getY() >= vars.dynamic.CapitalHeight * 0.8) &&
                (line_y - seg->getY() - SegmentTools::getRealHeight(*seg)) > vars.dynamic.CapitalHeight / 2)
            {
                possible_upperscript = true;
            }
            else if ((seg->getY() + SegmentTools::getRealHeight(*seg)) > line_y)
            {
                possible_subscript = true;
            }
        }

        if ((possible_upperscript || possible_subscript) && (pr.getBest() == 'l'))
        {
            pr.adjust(0.1, "1");
        }
        else if (possible_upperscript || possible_subscript)
        {
            pr.adjust(vars.labels.adjustInc, CharacterRecognizer::digits);
        }
        else
        {
            pr.adjust(vars.labels.adjustDec, substract(CharacterRecognizer::digits, "1"));
        }

        getLogExt().append("Ranged best candidates", pr.getRangedBest());

        if (vars.dynamic.CapitalHeight > 0)
        {
            double ratio = (double)SegmentTools::getRealHeight(*seg) / (vars.dynamic.CapitalHeight - 1);
            getLogExt().append("Height ratio", ratio);

            //			double base = 1.0 - vars.labels.ratioWeight * 1.0;
            //			pr.adjust(base + vars.labels.ratioWeight * ratio , CharacterRecognizer::lower + CharacterRecognizer::digits);

            pr.adjust(1.0 + (ratio - 0.8), substract(CharacterRecognizer::lower + CharacterRecognizer::digits + CharacterRecognizer::charges, "l1"));

            // complicated cases: there are some symbols with exactly the same representation in lower and upper cases
            // and this is first symbol for current atom
            if ((ratio > vars.labels.ratioCapital) && (_cur_atom->getLabelFirst() == 0))
            {
                std::string lower_em = lower(exact_as_lower);
                if (lower_em.find(pr.getBest()) != std::string::npos)
                {
                    pr.adjust(vars.labels.capitalAdjustFactor, exact_as_lower);
                }
            }
            /*
                                    else if (ratio > vars.labels.ratioCapital)
                                    {
                            std::string lower_em = lower(exact_as_lower);
                            if (lower_em.find(pr.getBest()) != std::string::npos)
                            {
            //					pr.adjust(vars.labels.adjustInc, exact_as_lower);
                                pr.adjust(vars.labels.capitalAdjustFactor, exact_as_lower);
                            }
                        }
            */
            else if ((ratio < 0.25) && (pr.getBest() != '+') && (pr.getBest() != '-'))
            {
                getLogExt().appendText("Too small symbol, probably some mech. Just ignore it");
                return;
            }
        }

        getLogExt().append("Ranged best candidates", pr.getRangedBest());
    }

    {
        // adjust using chemical structure logic

        if (_cur_atom->getLabelFirst() != 0 && _cur_atom->getLabelSecond() == 0)
        {
            // can be a capital or digit or small
            int idx = _cur_atom->getLabelFirst() - 'A';
            if (idx >= 0 && idx < 26)
            {
                if (_cur_atom->getLabelFirst() == 'C')
                    pr.adjust(vars.labels.adjustInc, "l");
                if ((_cur_atom->getLabelFirst() == 'C') && !possible_subscript && ((pr.getBest() == '1') || (pr.getBest() == 'I')))
                    pr.adjust(0.1, "l");
                if ((_cur_atom->getLabelFirst() == 'S') && ((pr.getBest() == 'l') || (pr.getBest() == '1')))
                    pr.adjust(0.1, "i");
                if ((_cur_atom->getLabelFirst() == 'O') && (pr.getBest() == 'l') && !possible_upperscript && !possible_subscript)
                    _cur_atom->setLabel("C");

                // decrease probability of unallowed characters
                pr.adjust(vars.labels.adjustDec, can_not_be_in_comb[idx]);

                // increase probability of small characters if first capital can not be just one symbol
                if (can_not_be_only_one_capital.find(_cur_atom->getLabelFirst()) != std::string::npos)
                {
                    pr.adjust(vars.labels.adjustInc, substract(CharacterRecognizer::lower, can_not_be_in_comb[idx]));
                }
            }
            else if ((_cur_atom->getLabelFirst() == ')') && (possible_subscript))
            {
                pr.adjust(vars.labels.adjustInc, CharacterRecognizer::digits);
            }
        }
        else if ((_cur_atom->getLabelFirst() == 0) && !possible_upperscript)
        {
            // should be a capital letter, increase probability of allowed characters
            pr.adjust(vars.labels.adjustInc, substract(CharacterRecognizer::upper, can_not_be_capital));
        }
    }

    int attempts_count = 0;

retry:

    if (attempts_count++ > vars.labels.adjustAttemptsCount)
    {
        getLogExt().append("Probably unrecognizable. Attempts count reached", attempts_count);
        return;
    }

    getLogExt().append("Ranged best candidates", pr.getRangedBest());
    getLogExt().append("Quality", pr.getQuality());

    char ch = pr.getBest();
    if ((CharacterRecognizer::upper.find(ch) != std::string::npos) ||
        (CharacterRecognizer::specials.find(ch) != std::string::npos)) // it also includes 'tricky' symbols
    {
        _addAtom();
        if (!_multiLetterSubst(ch)) // 'tricky'
        {
            getLogExt().append("Added first label", ch);
            _cur_atom->addLabel(pr);
        }
        else
        {
            getLogExt().append("Done multichar subst", ch);
        }
    }
    else if (CharacterRecognizer::lower.find(ch) != std::string::npos)
    {
        if (_cur_atom->getLabelSecond() != 0)
        {
            getLogExt().appendText("Small letter comes after another small, fixup & retry");
            pr.adjust(vars.labels.adjustDec, CharacterRecognizer::lower);
            goto retry;
        }
        else if (_cur_atom->getLabelFirst() == 0)
        {
            getLogExt().appendText("Small specified for non-set captial, fixup & retry");
            pr.adjust(vars.labels.adjustDec, CharacterRecognizer::lower);
            goto retry;
        }
        else
        {
            getLogExt().append("Added second label", ch);
            _cur_atom->addLabel(pr);
        }
    }
    else if (CharacterRecognizer::digits.find(ch) != std::string::npos)
    {
        /*
                if (_cur_atom->count != 0)
                {
                    getLogExt().appendText("Count specified twice, fixup & retry");
                    pr.adjust(vars.labels.adjustDec, CharacterRecognizer::digits);
                    goto retry;
                }
        */
        if ((_cur_atom->getLabelFirst() == 0) && !possible_upperscript)
        {
            getLogExt().appendText("Count specified for non-set atom, fixup & retry");
            pr.adjust(vars.labels.adjustDec, CharacterRecognizer::digits);
            goto retry;
        }
        else
        {
            int digit = ch - '0';
            if (_cur_atom->getLabelFirst() == 'R' && _cur_atom->getLabelSecond() == 0)
            {
                _cur_atom->charge = _cur_atom->charge * 10 + digit;
                getLogExt().append("Initialized R-group index", _cur_atom->charge);
            }
            else if (!possible_upperscript)
            {
                _cur_atom->count = _cur_atom->count * 10 + digit;
                getLogExt().append("Initialized atom count", _cur_atom->count);
            }
            else if (_cur_atom->getLabelFirst() != 0)
            {
                getLogExt().append("Current atom charge", _cur_atom->charge);

                if (_cur_atom->charge == 0)
                    _cur_atom->charge = digit;
                else
                    _cur_atom->charge = _cur_atom->charge * digit;

                getLogExt().append("Initialized atom charge", _cur_atom->charge);
            }
            else
            {
                _cur_atom->isotope = _cur_atom->isotope * 10 + digit;
                getLogExt().append("Initialized atom isotope", _cur_atom->isotope);
            }
        }
    }
    else if (CharacterRecognizer::brackets.find(ch) != std::string::npos) // brackets
    {
        _addAtom();
        _cur_atom->addLabel(pr);
        getLogExt().append("Added bracket", ch);
    }
    else if (CharacterRecognizer::charges.find(ch) != std::string::npos) // charges
    {
        // Special check fo possible chain construction
        // just ignore this symbol in that case
        if (ch == '-' && !possible_upperscript)
        {
            getLogExt().appendText("Possible chain found. Just ignore minus sign in that case!");
            return;
        }

        if (_cur_atom->getLabelFirst() == 0)
        {
            getLogExt().appendText("Atom charge specified for non-set atom. Try to process this label later");
            return;
        }

        getLogExt().append("Current atom charge", _cur_atom->charge);
        if (_cur_atom->charge == 0)
            _cur_atom->charge = (ch == '+') ? +1 : -1;
        else
            _cur_atom->charge = _cur_atom->charge * ((ch == '+') ? +1 : -1);

        getLogExt().append("Initialized atom charge", _cur_atom->charge);
    }
    else
    {
        getLogExt().append("Current char not in supported set, increase probability of supported ones", ch);
        pr.adjust(vars.labels.adjustInc, CharacterRecognizer::all);
        goto retry;
    }
}

void LabelLogic::_addAtom()
{
    if (_cur_atom && _cur_atom->getLabelFirst() == 0 && _cur_atom->getLabelSecond() == 0)
        return;

    _satom->atoms.resize(_satom->atoms.size() + 1);
    _cur_atom = &_satom->atoms[_satom->atoms.size() - 1];
}

bool LabelLogic::_multiLetterSubst(char sym)
{
    switch (sym)
    {
    case '$':
        _cur_atom->setLabel("F");
        _cur_atom->count = 3;
        return true;
    case '%':
        _cur_atom->setLabel("H");
        _cur_atom->count = 2;
        return true;
    case '^':
        _cur_atom->setLabel("H");
        _cur_atom->count = 3;
        return true;
    case '&':
        _cur_atom->setLabel("O");
        _addAtom();
        _cur_atom->setLabel("C");
        return true;
    case '#':
        _cur_atom->setLabel("N");
        _addAtom();
        _cur_atom->setLabel("H");
        return true;
    case '=':
        // special chars to ignore
        return true;
    }

    return false;
}

void LabelLogic::_buildPossibleCombArray()
{
    for (int i = 0; i < 26; i++)
    {
        char ch = 'A' + i;
        std::string allowed = "";
        for (std::string el : AtomMap.Elements)
        {
            char c_str[2] = {0};
            for (size_t c = 0; c < el.size() && c < 2; c++)
                c_str[c] = el[c];
            if (ch == c_str[0] && c_str[1] != 0)
            {
                allowed.push_back(c_str[1]);
            }
        }
        std::sort(allowed.begin(), allowed.end());
        allowed_comb[i] = allowed;
        getLogExt().append("", ch);
        getLogExt().appendText(substract(CharacterRecognizer::lower, allowed_comb[i]));
        getLogExt().appendText(can_not_be_in_comb[i]);
    }
}

void LabelLogic::_postProcessLabel(Label& label)
{
    logEnterFunction();

    Superatom& sa = label.satom;

    if (sa.atoms.size() > 0)
    {
        getLogExt().append("Molecule", sa.getPrintableForm());

        ChemicalValidity validator;
        double pr = validator.getLabelProbability(sa);
        getLogExt().append("probability", pr);

        if (pr < EPS)
        {
            getLogExt().appendText("Got wrong label!");
            validator.updateAlternative(sa);
            getLogExt().append("Used as alternative", sa.getPrintableForm());
        }
    }

    // old hack removing extra hydrogen
    if (sa.atoms.size() == 2)
    {
        for (size_t i = 0; i < 2; i++)
        {
            Atom& atom = sa.atoms[i];
            if (atom.getLabelFirst() == 'H' && atom.getLabelSecond() == 0 && atom.charge == 0 && atom.isotope == 0)
            {
                sa.atoms.erase(sa.atoms.begin() + i);
                break;
            }
        }
    }

    // more safe hack for empty labels
    if (sa.atoms.size() == 0)
    {
        Atom placeholder;
        placeholder.setLabel("H");
        sa.atoms.push_back(placeholder);
    }
    else if (sa.atoms.size() == 1 && sa.atoms[0].getLabelFirst() == 0)
    {
        sa.atoms[0].setLabel("H");
    }
}

void LabelLogic::checkUnmappedLabels(const Settings& vars, std::deque<Label>& unmapped_labels, std::deque<Label>& labels)
{
    logEnterFunction();

    for (Label& ul : unmapped_labels)
    {
        for (Label& l : labels)
        {
            if ((_isPossibleSubscript(vars, ul, l)) || (_isPossibleChain(vars, ul, l)))
            {
                l.satom.atoms.clear();
                l.symbols.insert(l.symbols.end(), ul.symbols.begin(), ul.symbols.end());
                LabelCombiner::fillLabelInfo(vars, l, _cr);
                recognizeLabel(vars, l);
            }
        }
    }
}

bool LabelLogic::_isPossibleSubscript(const Settings& vars, Label& subscript, Label& label)
{
    if ((subscript.rect.x == label.rect.x) && (subscript.rect.y == label.rect.y) && (subscript.rect.width == label.rect.width) &&
        (subscript.rect.height == label.rect.height))
        return false;

    if (Rectangle::distance(subscript.rect, label.rect) < vars.dynamic.CapitalHeight)
    {
        if (((label.rect.x >= (subscript.rect.x + subscript.rect.width)) && (subscript.rect.y < label.rect.y)) ||
            ((subscript.rect.x >= (label.rect.x + label.rect.width)) && (subscript.rect.y < label.rect.y)) ||
            ((subscript.rect.x >= (label.rect.x + label.rect.width)) && (subscript.rect.y > label.rect.y)))
            return true;
    }
    return false;
}

bool LabelLogic::_isPossibleChain(const Settings& vars, Label& tail, Label& label)
{
    if ((tail.rect.x == label.rect.x) && (tail.rect.y == label.rect.y) && (tail.rect.width == label.rect.width) && (tail.rect.height == label.rect.height))
        return false;

    if (Rectangle::distance(tail.rect, label.rect) < vars.dynamic.CapitalHeight)
    {
        return true;
    }
    return false;
}

void LabelLogic::recognizeLabel(const Settings& vars, Label& label)
{
    logEnterFunction();

    setSuperatom(&label.satom);

    {
        Segment temp(vars.general.ImageWidth, vars.general.ImageHeight, 0, 0);
        temp.fillWhite();
        for (size_t i = 0; i < label.symbols.size(); i++)
            ImageUtils::putSegment(temp, *label.symbols[i]);
        getLogExt().appendSegmentWithYLine(vars, "Source label", temp, label.baseline_y);
    }

    getLogExt().append("symbols count", label.symbols.size());
    if (label.multiline)
    {
        getLogExt().appendText("Multiline label");
    }
    else
    {
        getLogExt().append("label.baseline_y", label.baseline_y);
    }

    for (size_t i = 0; i < label.symbols.size(); i++)
    {
        try
        {
            process_ext(vars, label.symbols[i], label.multiline ? -1 : label.baseline_y);
        }
        catch (ImagoException& e)
        {
            getLogExt().append("Exception", e.what());
        }
    }

    _postProcessLabel(label);
}
