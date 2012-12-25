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
#include "small_character_recognizer.h"

using namespace imago;

LabelLogic::LabelLogic( const CharacterRecognizer &cr ) : _cr(cr), _satom(NULL), _cur_atom(NULL)
{
   flushed = was_charge = was_letter = was_super = 0;
}

LabelLogic::~LabelLogic()
{
}

void LabelLogic::setSuperatom( Superatom *satom )
{
	_cur_atom = NULL;
   _satom = satom;
   _addAtom();
   flushed = 1;
   was_super = was_letter = was_charge = 0;
}

const static char *comb[28] = // TODO: move to config
{
/*A*/   "lcmsur",
/*B*/   "aehkrnzou", 
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
/*R*/   "bhuena1236", // R-groups too
/*S*/   "iecbnrg",
/*T*/   "filaechmb",
/*U*/   "",
/*V*/   "",
/*W*/   "",
/*X*/   "e",
/*Y*/   "b",
/*Z*/   "nr",
		"ABCEFGHIKLMNOPQRSTUVWYZX$%^&#=()",
        "abcdeghiklmnoprstuyz",
};

void LabelLogic::_predict(const Settings& vars, const Segment *seg, std::string &letters )
{
	logEnterFunction();
   
   letters.clear();

   letters = comb[26]; //All capital letters
   
   if (_cur_atom->getLabelFirst() == 0)
   {
	   getLogExt().appendText("No label_first, exit");
       return;
   }

   if (_cur_atom->getLabelSecond() == 0)
   {
	   if (_cur_atom->getLabelFirst() == 'C')
	  {
		  getLogExt().appendText("label_first is C branch");
         letters.erase(letters.begin() + 7); //cuz of D
	  }
	   if (_cur_atom->getLabelFirst() == 'E')
	  {
		  getLogExt().appendText("label_first is E branch");
         letters.erase(letters.begin() + 8);
	  }
	   if (_cur_atom->getLabelFirst() == 'A')
	  {
		  getLogExt().appendText("label_first is A branch");
         letters.erase(letters.begin() + 7); //cuz of Al
	  }

	  if (seg->getHeight() <= vars.labels.capHeightError * vars.dynamic.CapitalHeight)
	  {
		  getLogExt().appendText("Too small height branch");
         letters.clear();
	  }

	  if (_cur_atom->getLabelFirst() == '?')
	  {
		  getLogExt().appendText("All small letters branch");
		  letters = CharacterRecognizer::lower;
	  }

	  else if(_cur_atom->getLabelFirst() >= 'A' && _cur_atom->getLabelFirst() <= 'Z') //just for sure 
		  for (size_t i = 0; i < strlen(comb[_cur_atom->getLabelFirst() - 'A']); i++)
			  letters.push_back(comb[_cur_atom->getLabelFirst() - 'A'][i]);
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


void LabelLogic::process_ext(const Settings& vars, Segment *seg, int line_y )
{
	logEnterFunction();
	getLogExt().appendSegmentWithYLine(vars, "segment with baseline", *seg, line_y);

	RecognitionDistance pr = _cr.recognize(vars, *seg);

	// acquire image params
	double underline = SegmentTools::getPercentageUnderLine(*seg, line_y);
	double ratio = (double)SegmentTools::getRealHeight(*seg) / vars.dynamic.CapitalHeight;

	{ // adjust using image params
		getLogExt().append("Percentage under baseline", underline);
		// assume the n% underline is zero-point
		pr.adjust(1.0 - vars.labels.weightUnderline * (underline - vars.labels.underlinePos), CharacterRecognizer::digits);		
	
		getLogExt().append("Height ratio", ratio);
		// assume the n% height ratio is zero-point
		pr.adjust(vars.labels.ratioBase + vars.labels.ratioWeight * ratio , CharacterRecognizer::lower + CharacterRecognizer::digits);	
	}

	{ // adjust using chemical structure logic
		if (_cur_atom->getLabelFirst() != 0 && _cur_atom->getLabelSecond() == 0)
		{
			// can be a capital or digit or small
			int idx = _cur_atom->getLabelFirst() - 'A';
			if (idx >= 0 && idx < 26)
			{
				// decrease probability of unallowed characters
				pr.adjust(vars.labels.adjustDec, substract(CharacterRecognizer::lower, comb[idx]));		
			}
		} 
		else if (_cur_atom->getLabelFirst() == 0)
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
			_cur_atom->addLabel(pr); // = ch;
		}
		was_letter = true;
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
			_cur_atom->addLabel(pr); // = ch;
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
		else if (_cur_atom->getLabelFirst() == 0)
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

void LabelLogic::_addAtom()
{
	if (_cur_atom && _cur_atom->getLabelFirst() == 0 && _cur_atom->getLabelSecond() == 0)
		return;

	_satom->atoms.resize(_satom->atoms.size() + 1);
	_cur_atom = &_satom->atoms[_satom->atoms.size() - 1];
}

bool LabelLogic::_multiLetterSubst(char sym)
{
	switch(sym)
	{
	case '$':
		_cur_atom->setLabel("Cl");
		was_letter = 0;
		return true;
	case '%':
		_cur_atom->setLabel("H");
		_cur_atom->count = 2;
		was_letter = 0;
		return true;
	case '^':
		_cur_atom->setLabel("H");
		_cur_atom->count = 3;
		was_letter = 0;
		return true;
	case '&':
		_cur_atom->setLabel("O");
		_addAtom();
		_cur_atom->setLabel("C");
		was_letter = 0;
		return true;
	case '#':
		_cur_atom->setLabel("N");
		_addAtom();
		_cur_atom->setLabel("H");
		//_cur_atom->count = 2;
		was_letter = 1;
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
	logEnterFunction();
	
	getLogExt().appendSegmentWithYLine(vars, "segment with baseline", *seg, line_y);

   std::string letters;
   int index_val = 0;

   double sameLineEps = vars.labels.sameLineEps;

   bool capital = false;
   int digit_small = -1;
   RecognitionDistance rd = _cr.recognize(vars, *seg, CharacterRecognizer::all, true);

   char hwc = rd.getBest();

   bool plus = ImageUtils::testPlus(vars, *seg);

   getLogExt().append("plus", plus);

   if (seg->getHeight() > vars.labels.heightRatio * vars.dynamic.CapitalHeight && (hwc == -1 || hwc < '0' || hwc > '9'))
      capital = true;
   else if ((hwc == -1 || hwc == '+') && plus)
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
		 c_big = _cr.recognize(vars, *seg, CharacterRecognizer::upper).getBest(&d_big);
		 getLogExt().append("c_big", c_big);
		 c_small = _cr.recognize(vars, *seg, CharacterRecognizer::lower).getBest(&d_small);
		 getLogExt().append("c_small", c_small);
		 c_digit = _cr.recognize(vars, *seg, CharacterRecognizer::digits).getBest(&d_digit);
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
               if (d_small + SMALL_EPS < d_digit)
                  capital = true;
               else
                  capital = false;
            }
            else
            {
				if (d_small + SMALL_EPS < d_digit)
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
   }

   getLogExt().append("capital", capital);
   
   if (capital)
   {
      //Check for tall small letters
      _predict(vars, seg, letters);
      char sym = hwc;

	  // probably this checking is outdated
      if (sym == 'N')
         ;
      else if (sym == 'H')
         ;
      else if (sym == 'O')
         ;
      else if (seg->getFeatures().recognizable)
		  sym = _cr.recognize(vars, *seg, letters).getBest(); //TODO: Can use c_big here
      else
         sym = '?';

	  // probably this checking is outdated too
      if (sym == 'o' || sym == 'c' || sym == 's' ||
          sym == 'i' || sym == 'p' || sym == 'u' ||
          sym == 'v' || sym == 'w')
         sym = toupper(sym);

	  getLogExt().append("LLogic sym", sym);
      
      if (sym >= 'a' && sym <= 'z')
      {
         if (was_letter)
         {
			 _cur_atom->addLabel(sym); // TODO: probability table too
         }
         else
            throw LabelException("Unexpected symbol position");
      }
      else
      {
		  //  ------------------------------ evil hack section ------------------------------
		  if (sym > '0' && sym <= '9' && _cur_atom->getLabelFirst() == 'R')
		  {
			  getLogExt().appendText("Hack works! R-group");
			  _cur_atom->charge = sym - '0';
			  was_charge = 1;
			  was_letter = 0;
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
				 _cur_atom->addLabel(sym); // TODO: probability table too
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
      if (bottom >= (line_y - sameLineEps * vars.dynamic.CapitalHeight) &&
          bottom <= (line_y + sameLineEps * vars.dynamic.CapitalHeight) &&
          (digit_small == -1 || digit_small == 1) && !plus)
      {
		  getLogExt().appendText("small");
         if (was_letter)
         {
			 getLogExt().append("letters", letters);
            _predict(vars, seg, letters);
            if (seg->getFeatures().recognizable)
			{
				_cur_atom->addLabel(_cr.recognize(vars, *seg, letters).getBest());
			}
            /*else
               _cur_atom->label_second = '?';*/
         }
         else
            throw LabelException("Unexpected symbol position (small instead of capital)");
      }
      //superscript
      else if (plus || med < line_y - vars.labels.medHeightFactor * vars.dynamic.CapitalHeight && digit_small == 0)
      {
		  getLogExt().appendText("superscript");
         was_super = 1;
         if (was_charge)
         {
            _addAtom();

            was_charge = 0;
            flushed = 1;
         }
         //Isotope
		 if (_cur_atom->getLabelFirst() == 0)
         {
			 getLogExt().appendText("isotope");
            if (seg->getFeatures().recognizable)
				index_val = _cr.recognize(vars, *seg, CharacterRecognizer::digits).getBest() - '0';
            else
               index_val = 0;
            _cur_atom->isotope = _cur_atom->isotope * 10 + index_val;
         }
         //Charge of current atom plus sign of charge
         else
         {
			 getLogExt().appendText("normal");
            char tmp;
            //Checking if current segment is + or -
            if (plus) //ImageUtils::testPlus(*seg))
            {
               tmp = '+';
            }
			else if (ImageUtils::testMinus(vars, *seg, (int)vars.dynamic.CapitalHeight)) //testMinus
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
				   tmp = _cr.recognize(vars, *seg, letters).getBest();
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
	  else if (med > line_y - vars.labels.medHeightFactor * vars.dynamic.CapitalHeight)
      {
		  getLogExt().appendText("subscript2");
		  
		  // the subscript shouldn't appear before any letter
		  if (_cur_atom->getLabelFirst() == 0)
            throw LabelException("Unexpected symbol position (subscript instaed of capital)");

         if (seg->getFeatures().recognizable)
		 {
			 index_val = _cr.recognize(vars, *seg, CharacterRecognizer::digits).getBest() - '0';
			getLogExt().append("Index val", index_val);
		 }
         else
		 {
            index_val = 0;
			getLogExt().append("not recognizable", index_val);
		 }

		 if (_cur_atom->getLabelFirst() == 'R')
		 {			 
			 _cur_atom->charge = _cur_atom->charge * 10 + index_val;
			 getLogExt().append("R-group", _cur_atom->charge);
		 }
		 else
		 {			 
			_cur_atom->count = _cur_atom->count * 10 + index_val;
			getLogExt().append("Count", _cur_atom->count);
		 }
      }
      else
      {
		  getLogExt().appendText("undefined");
         throw LabelException("Unexpected symbol position (else)");
      }
      was_letter = 0;
   }
}

void LabelLogic::_postProcessLabel(Label& label)
{
	logEnterFunction();

	Superatom &sa = label.satom;

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
			if (sa.atoms[i].getLabelFirst() == 'H' && sa.atoms[i].getLabelSecond() == 0 &&
				sa.atoms[i].charge == 0 && sa.atoms[i].isotope == 0)
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
