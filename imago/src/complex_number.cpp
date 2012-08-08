/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
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

#include "complex_number.h"
#include <cmath>

using namespace imago;



ComplexNumber::ComplexNumber(double Real, double Imaginary)
{
	_a = Real;
	_b = Imaginary;
}

ComplexNumber& ComplexNumber::operator*()
{
	return *this;
}

ComplexNumber& ComplexNumber::operator+ (ComplexNumber n2)
{
	_a += n2.getReal();
	_b += n2.getImaginary();
	return *this;
}

ComplexNumber& ComplexNumber::operator/(double n)
{
	_a /= n;
	_b/= n;
	return *this;
}

ComplexNumber& ComplexNumber::operator/=(double n)
{
	_a /= n;
	_b /= n;
	return *this;
}

ComplexNumber& ComplexNumber::operator*(double n)
{
	_a *= n;
	_b *= n;
	return *this;
}

ComplexNumber& ComplexNumber::operator*=(double n)
{
	_a *= n;
	_b *= n;
	return *this;
}

ComplexNumber ComplexNumber::Dot(ComplexNumber n1, ComplexNumber n2)
{
	double a1 = n1.getReal();
	double a2 = n2.getReal();
	double b1 = n1.getImaginary();
	double b2  = n2.getImaginary();

	return ComplexNumber(a1*a2 + b1*b2, b1*a2-a1*b2) ;
}

ComplexNumber  ComplexNumber::operator *(ComplexNumber n2)
{
	double radius = getRadius() * n2.getRadius();
	double angle = getAngle() + n2.getAngle();

	return ComplexNumber(radius * cos(angle), radius * sin(angle));
}