/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#include <map>
#include <string>

#include "exception.h"
#include "recognition_settings.h"

using namespace imago;

RecognitionSettings::RecognitionSettings()
{  
   initConfig(0);   
}

void RecognitionSettings::initConfig( int number )
{
   if (number >= CONF_COUNT || number < 0)
      throw LogicException("Invalid config number");

   const char *names[] = { "CfgNumber",
      "CapHeightErr",
      "BinarizationLvl",
      "Filter",
      "MaxSymRatio",
      "MinSymRatio",
      "SuperSegWndSize",
      "SuspSegDensity",
      "ParLinesEps",
      "AddVertexEps",
      "SameLineEps",
      "DebugSession" };

   const int names_size = (int)(sizeof(names) / sizeof(names[0]));

   RecognitionSettings::Parameter values[CONF_COUNT][names_size] = {
      { 0, 0.85, 200, "none",  1.14, 0.34, 40, 0.2,  0.34, 5.2, 0.08, false },
      { 1, 0.87, 220, "blur",  1.14, 0.34, 40, 0.3,  0.34, 5.2, 0.11, false },
      { 2, 0.78, 200, "sharp", 1.14, 0.34, 40, 0.3,  0.4,  5.8, 0.13, false },
      { 3, 0.85, 150, "none",  1.14, 0.34, 40, 0.25, 0.44, 5.2, 0.1, false },
      { 4, 0.82, 150, "blur",  1.14, 0.34, 40, 0.3,  0.34, 5.2, 0.1, false } };

   for (int i = 0; i != names_size; i++)
      set(names[i], values[number][i]);
}

RecognitionSettings::Parameter RecognitionSettings::get( const std::string &name )
{
   NameToParMap::iterator it = _storage.find(name);

   if (it == _storage.end())
      throw InvalidNameException("Name %s\n", name.c_str());

   return it->second;
}

RecognitionSettings::Parameter & imago::RecognitionSettings::operator[]( const std::string &name )
{
   NameToParMap::iterator it = _storage.find(name);

   if (it == _storage.end())
      throw InvalidNameException("Name %s\n", name.c_str());

   return it->second;
}

RecognitionSettings::~RecognitionSettings()
{
   int b = 0;
}