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

#pragma once

#include <map>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include "recognition_distance.h"
#include "segment.h"
#include "segment_tools.h"
#include "settings.h"
#include "stl_fwd.h"

namespace imago
{
    class Segment;

    class CharacterRecognizer
    {
    public:
        bool isPossibleCharacter(const Settings& vars, const Segment& seg, bool loose_cmp = false, char* result = NULL);

        RecognitionDistance recognize(const Settings& vars, const Segment& seg, const std::string& candidates = all) const;

        virtual ~CharacterRecognizer(){};

        static const std::string upper;
        static const std::string lower;
        static const std::string digits;
        static const std::string charges;
        static const std::string brackets;
        static const std::string all;
        static const std::string graphics;
        static const std::string like_bonds;
        static const std::string specials;

    private:
        static qword getSegmentHash(const Segment& seg);
    };

    namespace CharacterRecognizerImp
    {
        const int REQUIRED_SIZE = 30;
        const int PENALTY_SHIFT = 1;
        const int PENALTY_STEP = 1;

        // used for technical reasons, do not modify
        const int PENALTY_WHITE_FACTOR = 32;
        const int CHARACTERS_OFFSET = 32;
        const int INTERNAL_ARRAY_DIM = REQUIRED_SIZE + 2 * PENALTY_SHIFT;
        const int INTERNAL_ARRAY_SIZE = INTERNAL_ARRAY_DIM * INTERNAL_ARRAY_DIM;

        struct MatchRecord
        {
            unsigned char penalty_ink[INTERNAL_ARRAY_SIZE];
            unsigned char penalty_white[INTERNAL_ARRAY_SIZE];
            std::string text;
            double wh_ratio;
        };

        typedef std::vector<MatchRecord> Templates;

        void calculatePenalties(const cv::Mat1b& img, unsigned char* penalty_ink, unsigned char* penalty_white);
        double compareImages(const cv::Mat1b& img, const unsigned char* penalty_ink, const unsigned char* penalty_white);
        double compareImages2(const cv::Mat1b& img, const unsigned char* penalty_ink, const unsigned char* penalty_white);
        cv::Mat1b prepareImage(const Settings& vars, const cv::Mat1b& src, double& ratio);
        bool initializeTemplates(const Settings& vars, const std::string& path, Templates& templates);
        RecognitionDistance recognizeMat(const Settings& vars, const cv::Mat1b& image, const Templates& templates);
    };
}
