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
#ifndef _molecule_h
#define _molecule_h

#include <map>

#include "comdef.h"
#include "skeleton.h"
#include "label_combiner.h"
#include "settings.h"

namespace imago
{
   class Molecule : public Skeleton
   {
   public:

      typedef std::map<Skeleton::Vertex, Label*> ChemMapping;

      Molecule();

      const ChemMapping &getMappedLabels() const;
      ChemMapping &getMappedLabels();

      const std::deque<Label> &getLabels() const;
      std::deque<Label> &getLabels();

      const SkeletonGraph &getSkeleton() const;
      SkeletonGraph &getSkeleton();

      void aromatize( Points2d &p );

      void mapLabels(const Settings& vars, std::deque<Label> &unmapped_labels );

      void clear();

      ~Molecule();

   private:
      ChemMapping _mapping;
      std::deque<Label> _labels;
      std::vector<Label> labels;
   };
}


#endif /* _molecule_h */
