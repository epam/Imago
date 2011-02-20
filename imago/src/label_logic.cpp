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

#include <cstring>
#include <ctype.h>

#include "label_logic.h"
#include "segment.h"
#include "character_recognizer.h"
#include "label_combiner.h"
#include "image_utils.h"
#include "current_session.h"

using namespace imago;

LabelLogic::LabelLogic( const CharacterRecognizer &cr, double capHeightError ) :
_cr(cr),
   cap_height_error(capHeightError) //0.82 0.877 0.78
{
   cap_height_error = 0.56; //changed in "handwriting"
   _cap_height = (int)getSettings()["CapitalHeight"];
   flushed = was_charge = was_letter = was_super = 0;
}

LabelLogic::~LabelLogic()
{
}

void LabelLogic::setSuperatom( Superatom *satom )
{
   //Uncomment if you want to follow the standarts
   //if (was_super && !was_charge)
   //   throw ERROR("Unexpected symbol position (isotope or charge)");

   _satom = satom;
   satom->atoms.resize(satom->atoms.size() + 1);
   _cur_atom = &satom->atoms[satom->atoms.size() - 1];
   flushed = 1;
   was_super = was_letter = was_charge = 0;
}

void LabelLogic::_predict( const Segment *seg, std::string &letters )
{
   const static char *comb[28] = //"Constants", not config but name ?
   {
   /*A*/   "lcmsur",//tgl
   /*B*/   "aehkrnz", //i
   /*C*/   "aoldrsef",
   /*D*/   "by",
   /*E*/   "turs",
   /*F*/   "er",
   /*G*/   "aed",
   /*H*/   "efgso",
   /*I*/   "",
   /*J*/   "",
   /*K*/   "r",
   /*L*/   "iau",
   /*M*/   "egnotd",
   /*N*/   "aeibdop",
   /*O*/   "s",
   /*P*/   "hdtormu",
   /*Q*/   "",
   /*R*/   "bhuena",
   /*S*/   "iecbnrg",
   /*T*/   "ilaechmb",
   /*U*/   "",
   /*V*/   "",
   /*W*/   "",
   /*X*/   "e",
   /*Y*/   "b",
   /*Z*/   "nr",
           "ABCEFGHIKLMNOPQRSTUVWYZX", //XD //K removed in "handwriting"
           "abcdeghiklmnoprstuyz",
   };
   
   letters.clear();

   letters = comb[26]; //All capital letters
   
   if (_cur_atom->label_first == 0)
      return;

   if (_cur_atom->label_second == 0)
   {
      if (_cur_atom->label_first == 'C')
         letters.erase(letters.begin() + 7); //cuz of D
      if (_cur_atom->label_first == 'E')
         letters.erase(letters.begin() + 8);
      if (_cur_atom->label_first == 'A')
         letters.erase(letters.begin() + 7); //cuz of Al

      if (seg->getHeight() <= cap_height_error * _cap_height)
         letters.clear();

      if (_cur_atom->label_first == '?')
         letters = comb[27]; //All small letters
      else if(_cur_atom->label_first >= 'A' && _cur_atom->label_first <= 'Z') //just for sure 
         for (int i = 0; i < (int)strlen(comb[_cur_atom->label_first - 'A']); i++)
            letters.push_back(comb[_cur_atom->label_first - 'A'][i]);
   }
}

void LabelLogic::_postProcess()
{
   if (_cur_atom->label_first == 0)
   {
      _cur_atom->label_first = '?';
      _cur_atom->label_second = 0;
   }

   if (!was_charge && _cur_atom->charge != 0)
      _cur_atom->charge = 0;
}

void LabelLogic::process( Segment *seg, int line_y )
{
   std::string letters;
   int index_val = 0;

   double sameLineEps = 0.2; //(double)getSettings()["SameLineEps"];
                             //changed in "handwriting"
   bool capital = false;
   //TODO: This can slowdown recognition process! Check this!
   if (seg->getHeight() > 0.9 * _cap_height)
      capital = true;
   else
   {
      double d_big, d_small, d_digit;
      char c_big, c_small, c_digit;
      
      // No time to combine the recognizers properly. 
      // Just use one on top of another for now.
      char hwc = 
_hwcr.recognize(*seg);

      if (hwc == 'N')
         capital = true;
      else if (hwc == 'H')
         capital = true;
      else if (hwc == 'O')
         capital = true; // can be O or o or 0
      else if (seg->getFeatures().recognizable)
      {
         c_big = _cr.recognize(*seg, CharacterRecognizer::upper, &d_big);
         c_small = _cr.recognize(*seg, CharacterRecognizer::lower, &d_small);
         c_digit = _cr.recognize(*seg, CharacterRecognizer::digits, &d_digit);
         if (d_big < d_small + 0.00001 && d_big < d_digit + 0.00001)
            capital = true;
         else
         {
            if (c_small == 'o' || c_small == 'c' || c_small == 's' ||
                c_small == 'i' || c_small == 'p' || c_small == 'u' ||
                c_small == 'v' || c_small == 'w')
               capital = true;
            else
               capital = false;
         }
      }
   }
   
   if (capital) //seg->getHeight() > cap_height_error * _cap_height)
   {
      //Check for tall small letters
      _predict(seg, letters);
      char sym = _hwcr.recognize(*seg);

      if (sym == 'N')
         ;
      else if (sym == 'H')
         ;
      else if (sym == 'O')
         ;
      else if (seg->getFeatures().recognizable)
         sym = _cr.recognize(*seg, letters); //TODO: Can use c_big here
      else
         sym = '?';

      if (sym == 'o' || sym == 'c' || sym == 's' ||
          sym == 'i' || sym == 'p' || sym == 'u' ||
          sym == 'v' || sym == 'w')
         sym = toupper(sym);
      
      if (sym >= 'a' && sym <= 'z')
      {
         if (was_letter)
         {
            _cur_atom->label_second = sym;
         }
         else
            throw LabelException("Unexpected symbol position");
      }
      else
      {
         if (!flushed)
         {
            _postProcess();
            
            if (was_super && !was_charge)
            {
               int tmp = _cur_atom->charge;
               _satom->atoms.resize(_satom->atoms.size() + 1);
               _cur_atom = &_satom->atoms[_satom->atoms.size() - 1];
               _cur_atom->isotope = tmp;
            }
            else
            {
               _satom->atoms.resize(_satom->atoms.size() + 1);
               _cur_atom = &_satom->atoms[_satom->atoms.size() - 1];
            }
         }
         else
            flushed = 0;

         //TODO: Lowercase letter can be that height too!

         _cur_atom->label_first = sym;
         was_letter = 1;
         was_charge = 0;
         was_super = 0;
      }
   }
   else
   {
      int bottom = seg->getY() + seg->getHeight();
      int med = bottom - 0.5 * seg->getHeight();
      //small letter
      if (bottom >= (line_y - sameLineEps * _cap_height) &&
          bottom <= (line_y + sameLineEps * _cap_height))
      {
         if (was_letter)
         {
            _predict(seg, letters);
            if (seg->getFeatures().recognizable)
               _cur_atom->label_second = _cr.recognize(*seg, letters);
            else
               _cur_atom->label_second = '?';
         }
         else
            throw LabelException("Unexpected symbol position");
      }
      //superscript
      else if (med < line_y - 0.5 * _cap_height)
      {
         was_super = 1;
         if (was_charge)
         {
            _postProcess();

            _satom->atoms.resize(_satom->atoms.size() + 1);
            _cur_atom = &_satom->atoms[_satom->atoms.size() - 1];

            was_charge = 0;
            flushed = 1;
         }
         //Isotope
         if (_cur_atom->label_first == 0)
         {
            if (seg->getFeatures().recognizable)
               index_val = _cr.recognize(*seg, CharacterRecognizer::digits) - '0';
            else
               index_val = 0;
            _cur_atom->isotope = _cur_atom->isotope * 10 + index_val;
         }
         //Charge of current atom plus sign of charge
         else
         {
            char tmp;
            //Checking if current segment is + or -
            if (ImageUtils::testPlus(*seg))
            {
               tmp = '+';
            }
            else if (ImageUtils::testMinus(*seg, _cap_height)) //testMinus
            {
               tmp = '-';
            }
            else
            {
               if (_cur_atom->charge == 0)
                  letters = "123456789";
               else
                  letters = "0123456789";

               if (seg->getFeatures().recognizable)
                  tmp = _cr.recognize(*seg, letters);
               else
                  tmp = 0; //TODO: what to do if charge is unrecognizable
            }
            
            if (tmp == '-')
            {
               if (_cur_atom->charge == 0)
                  _cur_atom->charge = 1;
               
               _cur_atom->charge *= -1, was_charge = 1;
            }
            else if (tmp == '+')
            {
               if (_cur_atom->charge == 0)
                  _cur_atom->charge = 1;

               was_charge = 1;
            }
            else if (tmp >= '0' && tmp <= '9')
               _cur_atom->charge = _cur_atom->charge * 10 + (tmp - '0');
         }
      }
      //subscript
      else if (med > line_y - 0.5 * _cap_height)
      {
         //If subscript will appear before any letter, do some BADABUM
         if (_cur_atom->label_first == 0)
            throw LabelException("Unexpected symbol position");

         if (seg->getFeatures().recognizable)
            index_val = _cr.recognize(*seg, CharacterRecognizer::digits) - '0';
         else
            index_val = 0;
         _cur_atom->count = _cur_atom->count * 10 + index_val;
      }
      else
      {
         throw LabelException("Unexpected symbol position");
      }
      was_letter = 0;
   }
}

void LabelLogic::recognizeLabel( Label& label )
{
   setSuperatom(&label.satom);
   for (int i = 0; i < (int)label.symbols.size(); i++)
   {
      int y;
      if (label.multi_begin < 0 || i < label.multi_begin)
         y = label.line_y;
      else
         y = label.multi_line_y;

      try
      {
         process(label.symbols[i], y);
      }
      catch(OCRException &)
      {
         _postProcess();
      }
   }
   _postProcess();

   //Came here from Molecule::recognizeLabels
   Superatom &sa = label.satom;
   if (sa.atoms.size() == 2)
   {
      if (sa.atoms[0].label_first == 'H' && sa.atoms[0].label_second == 0 &&
          sa.atoms[0].charge == 0 && sa.atoms[0].isotope == 0)
      {
         sa.atoms.erase(sa.atoms.begin());
      }
      else if (sa.atoms[1].label_first == 'H' &&
               sa.atoms[1].label_second == 0 &&
               sa.atoms[1].charge == 0 && sa.atoms[1].isotope == 0)
      {
         sa.atoms.erase(sa.atoms.end() - 1);
      }
   }
}
