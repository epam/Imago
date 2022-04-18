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

/**
 * @file   complex_number.h
 * 
 * @brief  Complex numbers
 */

#pragma once
#ifndef _complex_number_h
#define _complex_number_h

#include <math.h>


namespace imago{

	class ComplexNumber
	  {
	  public:
		  ComplexNumber():_a(0.0), _b(0.0)
		  {}

		  ComplexNumber(double Real, double Imaginary);
		  
		  inline double getReal() const
		  { return _a; }

		  inline void setReal(double a)
		  { _a = a;}

		  inline double getImaginary() const
		  { return _b; }

		  inline void setImaginary(double b)
		  { _b = b;}

		  static ComplexNumber Dot(const ComplexNumber& n1, const ComplexNumber& n2);

		  ComplexNumber& operator*();
		  
		  const ComplexNumber& operator*() const;

		  ComplexNumber&  operator +(const ComplexNumber& n2);

		  ComplexNumber& operator +=(const ComplexNumber& cn)
		  {
			  _a += cn.getReal();
			  _b += cn.getImaginary();
			  return *this;
		  }

		  ComplexNumber operator -(const ComplexNumber& n)
		  {
			  return ComplexNumber(_a - n.getReal(), _b - n.getImaginary());
		  }

		  ComplexNumber& operator /(double n);

		  ComplexNumber& operator*(double n);

		  ComplexNumber& operator /=(double n);

		  ComplexNumber& operator *=(double n);

		  inline double getAngle() const
		  {
			  return atan2(_b, _a);
		  }

		  inline double getRadius() const
		  {
			  return sqrt(getRadius2());
		  }

		  inline double getRadius2() const
		  {
			  return _a * _a + _b * _b;
		  }

		  ComplexNumber  operator *(const ComplexNumber& n2);

	  private:
		  double _a, _b;
	  };
}
#endif
