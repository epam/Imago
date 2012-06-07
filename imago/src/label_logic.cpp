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
#include "log_ext.h"
#include "chemical_validity.h"

using namespace imago;

LabelLogic::LabelLogic( const CharacterRecognizer &cr ) : _cr(cr), _hwcr(cr), _satom(NULL), _cur_atom(NULL)
{
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

	_cur_atom = NULL;
   _satom = satom;
   _addAtom();
   flushed = 1;
   was_super = was_letter = was_charge = 0;
}

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
/*O*/   "sc",
/*P*/   "hdtormu",
/*Q*/   "",
/*R*/   "bhuena",
/*S*/   "iecbnrg",
/*T*/   "filaechmb",
/*U*/   "",
/*V*/   "",
/*W*/   "",
/*X*/   "e",
/*Y*/   "b",
/*Z*/   "nr",
		"ABCEFGHIKLMNOPQRSTUVWYZX$%^&#=", //XD //K removed in "handwriting"
        "abcdeghiklmnoprstuyz",
};

void LabelLogic::_predict(const Settings& vars, const Segment *seg, std::string &letters )
{
	logEnterFunction();
   
   letters.clear();

   letters = comb[26]; //All capital letters
   
   if (_cur_atom->label_first == 0)
   {
	   getLogExt().appendText("No label_first, exit");
       return;
   }

   if (_cur_atom->label_second == 0)
   {
      if (_cur_atom->label_first == 'C')
	  {
		  getLogExt().appendText("label_first is C branch");
         letters.erase(letters.begin() + 7); //cuz of D
	  }
      if (_cur_atom->label_first == 'E')
	  {
		  getLogExt().appendText("label_first is E branch");
         letters.erase(letters.begin() + 8);
	  }
      if (_cur_atom->label_first == 'A')
	  {
		  getLogExt().appendText("label_first is A branch");
         letters.erase(letters.begin() + 7); //cuz of Al
	  }

	  if (seg->getHeight() <= vars.labels.capHeightError * vars.estimation.CapitalHeight)
	  {
		  getLogExt().appendText("Too small height branch");
         letters.clear();
	  }

      if (_cur_atom->label_first == '?')
	  {
		  getLogExt().appendText("All small letters branch");
         letters = comb[27]; //All small letters
	  }

      else if(_cur_atom->label_first >= 'A' && _cur_atom->label_first <= 'Z') //just for sure 
         for (size_t i = 0; i < strlen(comb[_cur_atom->label_first - 'A']); i++)
            letters.push_back(comb[_cur_atom->label_first - 'A'][i]);
   }

   getLogExt().append("Letters", letters);
}

std::string substract(const std::string& fullset, const std::string& reduction)
{
	std::string result;
	for (std::string::const_iterator it = fullset.begin(); it != fullset.end(); it++)
		if (reduction.find(*it) == std::string::npos)
			result += *it;
	return result;
}

/*double calc_ratio(double max_amplitude, double value, double zero_point)
{
}*/

void LabelLogic::process_ext(const Settings& vars, Segment *seg, int line_y )
{
	logEnterFunction();
	getLogExt().appendSegmentWithYLine(vars, "segment with baseline", *seg, line_y);

	RecognitionDistance pr = _cr.recognize_all(vars, *seg);

	// acquire image params
	double underline = SegmentTools::getPercentageUnderLine(*seg, line_y);
	double ratio = (double)SegmentTools::getRealHeight(*seg) / vars.estimation.CapitalHeight;

	{ // adjust using image params
		getLogExt().append("Percentage under baseline", underline);
		// assume the n% underline is zero-point
		pr.adjust(1.0 - vars.labels.weightUnderline * (underline - vars.labels.underlinePos), CharacterRecognizer::digits);		
	
		getLogExt().append("Height ratio", ratio);
		// assume the n% height ratio is zero-point
		pr.adjust(vars.labels.ratioBase + vars.labels.ratioWeight * ratio , CharacterRecognizer::lower + CharacterRecognizer::digits);	
	}

	{ // adjust using chemical structure logic
		if (_cur_atom->label_first != 0 && _cur_atom->label_second == 0)
		{
			// can be a capital or digit or small
			int idx = _cur_atom->label_first - 'A';
			if (idx >= 0 && idx < 26)
			{
				// decrease probability of unallowed characters
				pr.adjust(vars.labels.adjustDec, substract(CharacterRecognizer::lower, comb[idx]));		
			}
		} 
		else if (_cur_atom->label_first == 0)
		{
			// should be a capital letter, increase probability of allowed characters
			pr.adjust(vars.labels.adjustInc, substract(CharacterRecognizer::upper, "XJUVWQ"));
		}
	}

	int attempts_count = 0;

	retry:

	if (attempts_count++ > 3)
	{
		getLogExt().appendText("Attempts count overreach 3, probably unrecognizable. skip");
		return;
	}

	getLogExt().appendMap("Current distance map", pr);
	//getLogExt().append("Ranged best candidates", pr.getRangedBest());
	getLogExt().append("Quality", pr.getQuality());


	char ch = pr.getBest();
	if (CharacterRecognizer::upper.find(ch) != std::string::npos) // it also includes 'tricky' symbols
	{
		_addAtom();
		if (!_multiLetterSubst(ch))
		{
			_cur_atom->label_first = ch;
		}
		was_letter = true;
	} 
	else if (CharacterRecognizer::lower.find(ch) != std::string::npos)
	{		
		if (_cur_atom->label_second != 0)
		{
			getLogExt().appendText("Small letter comes after another small, fixup & retry");
			pr.adjust(vars.labels.adjustDec, CharacterRecognizer::lower);
			goto retry;
		}
		else if (_cur_atom->label_first == 0)
		{
			getLogExt().appendText("Small specified for non-set captial, fixup & retry");
			pr.adjust(vars.labels.adjustDec, CharacterRecognizer::lower);
			goto retry;
		}
		else
		{
			_cur_atom->label_second = ch;
		}
	}
	else if (CharacterRecognizer::digits.find(ch) != std::string::npos)
	{
		if (_cur_atom->count != 0)
		{
			getLogExt().appendText("Count specified twice, fixup & retry");
			pr.adjust(vars.labels.adjustDec, CharacterRecognizer::digits);
			goto retry;
		}
		else if (_cur_atom->label_first == 0)
		{
			getLogExt().appendText("Count specified for non-set atom, fixup & retry");
			pr.adjust(vars.labels.adjustDec, CharacterRecognizer::digits);
			goto retry;
		}
		else
		{
			_cur_atom->count = ch - '0';
		}
	}
	else 
	{
		getLogExt().append("Current char not in supported set, skip", ch);
	}
}

void LabelLogic::_fixupSingleAtom()
{
   // TODO: remove

	// TODO: move these hacks to postprocess where the next atoms are already recognized
	/*
	if (_cur_atom && _cur_atom->label_first == 'A' && _cur_atom->label_second == 0)
	{
		getLogExt().appendText("Hack: A -> H");
		_cur_atom->label_first = 'H';
	}*/

	if (_cur_atom && _cur_atom->label_first == 'Q' && _cur_atom->label_second == 0)
	{
		getLogExt().appendText("Hack: Q -> C");
		_cur_atom->label_first = 'C';
	}
	if (_cur_atom && _cur_atom->label_first == 'X' && _cur_atom->label_second == 0)
	{
		getLogExt().appendText("Hack: X -> H");
		_cur_atom->label_first = 'H';
	}
	
   
	if (_cur_atom && _cur_atom->label_first == 'C' && _cur_atom->label_second == 'e')
	{
		getLogExt().appendText("Hack: Ce -> Cl");
		_cur_atom->label_second = 'l';
	}
}

void LabelLogic::_addAtom()
{
	if (_cur_atom && _cur_atom->label_first == 0 && _cur_atom->label_second == 0)
		return;

	_fixupSingleAtom();	

	_satom->atoms.resize(_satom->atoms.size() + 1);
	_cur_atom = &_satom->atoms[_satom->atoms.size() - 1];
}

bool LabelLogic::_multiLetterSubst(char sym)
{
	switch(sym)
	{
	case '$':
		_cur_atom->label_first = 'C';
		_cur_atom->label_second = 'l';
		was_letter = 0;
		return true;
	case '%':
		_cur_atom->label_first = 'H';
		_cur_atom->count = 2;
		was_letter = 0;
		return true;
	case '^':
		_cur_atom->label_first = 'H';
		_cur_atom->count = 3;
		was_letter = 0;
		return true;
	case '&':
		_cur_atom->label_first = 'O';
		_addAtom();
		_cur_atom->label_first = 'C';
		was_letter = 0;
		return true;
	case '#':
		_cur_atom->label_first = 'N';
		_addAtom();
		_cur_atom->label_first = 'H';
		_cur_atom->count = 2;
		was_letter = 0;
		return true;
	case '=':
		// special chars to ignore
		was_letter = 0;
		return true;
	}

	return false;
}

void LabelLogic::process(const Settings& vars, Segment *seg, int line_y )
{
   //ImageUtils::saveImageToFile(*seg, "output/aaa.png");

	logEnterFunction();

	getLogExt().appendSegmentWithYLine(vars, "segment with baseline", *seg, line_y);

   std::string letters;
   int index_val = 0;

   double sameLineEps = vars.labels.sameLineEps;

   bool capital = false;
   int digit_small = -1;
   char hwc = _hwcr.recognize(vars, *seg);

   bool plus = ImageUtils::testPlus(vars, *seg);

   getLogExt().append("plus", plus);

   //TODO: This can slowdown recognition process! Check this!
   if (seg->getHeight() > vars.labels.heightRatio * vars.estimation.CapitalHeight && (hwc == -1 || hwc < '0' || hwc > '9'))
      capital = true;
   else if (hwc == -1 && plus)
      capital = false;
   else
   {
      double d_big, d_small, d_digit;
      char c_big, c_small, c_digit;
      
      // No time to combine the recognizers properly. 
      // Just use one on top of another for now.
      if (hwc == 'N' || hwc == 'H' || hwc == 'O' || hwc == 'P')
         capital = true;
      else if (seg->getFeatures().recognizable)
      {
         c_big = _cr.recognize(vars, *seg, CharacterRecognizer::upper, &d_big);
		 getLogExt().append("c_big", c_big);
         c_small = _cr.recognize(vars, *seg, CharacterRecognizer::lower, &d_small);
		 getLogExt().append("c_small", c_small);
         c_digit = _cr.recognize(vars, *seg, CharacterRecognizer::digits, &d_digit);
		 getLogExt().append("c_digit", c_digit);

         if (d_big < d_small + SMALL_EPS && d_big < d_digit + SMALL_EPS) // eps
            capital = true;
         else
         {
            if (d_digit + SMALL_EPS < d_small) 
               digit_small = 0;
            else if (d_digit > d_small + SMALL_EPS) 
               digit_small = 1;
            
            if (c_small == 's' && c_digit == '2')
            {
               if (d_small < d_digit)
                  capital = true;
               else
                  capital = false;
            }
            else
            {
               if (c_small == 'o' || c_small == 'c' || c_small == 'i' ||
                   c_small == 'p' || c_small == 'u' ||
                   c_small == 'v' || c_small == 'w')
                  capital = true;
               else
                  capital = false;
            }
         }
      }
   }

   getLogExt().append("capital", capital);
   
   if (capital) //seg->getHeight() > cap_height_error * _cap_height)
   {
      //Check for tall small letters
      _predict(vars, seg, letters);
      char sym = hwc;

      if (sym == 'N')
         ;
      else if (sym == 'H')
         ;
      else if (sym == 'O')
         ;
      else if (seg->getFeatures().recognizable)
         sym = _cr.recognize(vars, *seg, letters); //TODO: Can use c_big here
      else
         sym = '?';

      if (sym == 'o' || sym == 'c' || sym == 's' ||
          sym == 'i' || sym == 'p' || sym == 'u' ||
          sym == 'v' || sym == 'w')
         sym = toupper(sym);

	  getLogExt().append("LLogic sym", sym);
      
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
		  //  ------------------------------ evil hack section ------------------------------
		  if (sym == 'I' && _cur_atom->label_first == 'I')
		  {
			  // HACK! II -> O
			  getLogExt().appendText("Hack works! II -> O");
			  _cur_atom->label_first = 'O';
			  was_letter = 1;
		  }
		  else if (sym == 'O' && _cur_atom->label_first == 'T')
		  {
			  // HACK! OTO -> OTF
			  getLogExt().appendText("Hack works! OTO -> OTF");
			  _addAtom();
			  _cur_atom->label_first = 'F';
			  was_letter = 1;
		  }
		  else if (sym == 'C' && _cur_atom->label_first == 'C')
		  {
			  // HACK! CC -> Cl
			  getLogExt().appendText("Hack works! CC -> Cl");
			  _addAtom();
			  _cur_atom->label_first = 'l';
			  was_letter = 1;
		  }
		  // ------------------------------ ------------------------------
		  else
		  {
			 if (!flushed)
			 {
				//_postProcess();
            
				if (was_super && !was_charge)
				{
				   int tmp = _cur_atom->charge;
				   _addAtom();
				   _cur_atom->isotope = tmp;
				}
				else
				{
				   _addAtom();
				}
			 }
			 else
				flushed = 0;

			 //TODO: Lowercase letter can be that height too!

			 if (!_multiLetterSubst(sym))
			 {
				_cur_atom->label_first = sym;
				was_letter = 1;
			 }
			 was_charge = 0;
			 was_super = 0;
		  }
      }
   }
   else
   {
      int bottom = seg->getY() + seg->getHeight();
      int med = bottom - seg->getHeight() / 2;
	  getLogExt().append("med", med);
      //small letter
      if (bottom >= (line_y - sameLineEps * vars.estimation.CapitalHeight) &&
          bottom <= (line_y + sameLineEps * vars.estimation.CapitalHeight) &&
          (digit_small == -1 || digit_small == 1))
      {
         if (was_letter)
         {
            _predict(vars, seg, letters);
            if (seg->getFeatures().recognizable)
			{
               _cur_atom->label_second = _cr.recognize(vars, *seg, letters);
			}
            else
               _cur_atom->label_second = '?';
         }
         else
            throw LabelException("Unexpected symbol position (small instead of capital)");
      }
      //superscript
      else if (med < line_y - vars.labels.medHeightFactor * vars.estimation.CapitalHeight && digit_small == 0)
      {
         was_super = 1;
         if (was_charge)
         {
            //_postProcess();

            _addAtom();

            was_charge = 0;
            flushed = 1;
         }
         //Isotope
         if (_cur_atom->label_first == 0)
         {
            if (seg->getFeatures().recognizable)
               index_val = _cr.recognize(vars, *seg, CharacterRecognizer::digits) - '0';
            else
               index_val = 0;
            _cur_atom->isotope = _cur_atom->isotope * 10 + index_val;
         }
         //Charge of current atom plus sign of charge
         else
         {
            char tmp;
            //Checking if current segment is + or -
            if (plus) //ImageUtils::testPlus(*seg))
            {
               tmp = '+';
            }
			else if (ImageUtils::testMinus(vars, *seg, (int)vars.estimation.CapitalHeight)) //testMinus
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
                  tmp = _cr.recognize(vars, *seg, letters);
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
	  else if (med > line_y - vars.labels.medHeightFactor * vars.estimation.CapitalHeight)
      {
         //If subscript will appear before any letter, do some BADABUM
         if (_cur_atom->label_first == 0)
            throw LabelException("Unexpected symbol position (subscript instaed of capital)");

         if (seg->getFeatures().recognizable)
            index_val = _cr.recognize(vars, *seg, CharacterRecognizer::digits) - '0';
         else
            index_val = 0;
         _cur_atom->count = _cur_atom->count * 10 + index_val;
      }
      else
      {
         throw LabelException("Unexpected symbol position (else)");
      }
      was_letter = 0;
   }
}

void LabelLogic::_postProcessLabel(Label& label)
{
	logEnterFunction();

	Superatom &sa = label.satom;

	std::string molecule = "";
	for (size_t i = 0; i < sa.atoms.size(); i++)
	{
		if (sa.atoms[i].label_first != 0) 
			molecule.push_back(sa.atoms[i].label_first);
		if (sa.atoms[i].label_second != 0) 
			molecule.push_back(sa.atoms[i].label_second);
	};

	ChemicalValidity cv;
	double pr = cv.getLabelProbability(molecule);
	getLogExt().append("Molecule", molecule);
	getLogExt().append("probability", pr);
	if (pr < EPS)
	{
		getLogExt().appendText("Got wrong label!");		

		std::vector<std::string> alt = cv.getAlternatives(molecule);
		if (!alt.empty()) // at least one alternative is better
		{
			// currently we have nothing left to lose; so forget about charges and isotopes.
			sa.atoms.clear();

			std::string update = alt[0];
			getLogExt().append("Used as alternative", update);

			for (size_t i = 0; i < update.length(); i++)
			{
				Atom a;
				a.label_first = update[i];
				// TODO: refactor this
				if (i+1 < update.length() && CharacterRecognizer::lower.find(update[i+1]) != std::string::npos)
				{
					a.label_second = update[i+1];
					i++;
				}
				sa.atoms.push_back(a);
			}
		}
	}

	if (sa.atoms.size() == 2)
	{
		for (size_t i = 0; i < 2; i++)
		{
			if (sa.atoms[i].label_first == 'H' && sa.atoms[i].label_second == 0 &&
				sa.atoms[i].charge == 0 && sa.atoms[i].isotope == 0)
			{
				sa.atoms.erase(sa.atoms.begin() + i);
				break;
			}
		}
	}
}


void LabelLogic::recognizeLabel(const Settings& vars, Label& label )
{
   logEnterFunction();

   setSuperatom(&label.satom);

   getLogExt().append("symbols count", label.symbols.size());
   getLogExt().append("label.multi_begin", label.multi_begin);

   for (size_t i = 0; i < label.symbols.size(); i++)
   {
      int y = label.multi_line_y;

	  if (label.multi_begin < 0 || (int)i < label.multi_begin)
         y = label.line_y;

	  getLogExt().append("i", i);
	  getLogExt().append("selected y", y);

      try
      {         
		 process(vars, label.symbols[i], y);
      }
      catch(ImagoException &e)
      {
		  try
		  {
			  getLogExt().append("Exception", e.what());
			  getLogExt().appendText("Give another try to process_ext() now");
			  process_ext(vars, label.symbols[i], y);
		  }
		  catch(ImagoException &e)
		  {
			  getLogExt().append("Exception", e.what());
		  }
      }      
   }

   _postProcessLabel(label);
}
