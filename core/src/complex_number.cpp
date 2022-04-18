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

const ComplexNumber& ComplexNumber::operator*() const
{
	return *this;
}

ComplexNumber& ComplexNumber::operator+ (const ComplexNumber& n2)
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

ComplexNumber ComplexNumber::Dot(const ComplexNumber& n1, const ComplexNumber& n2)
{
	double a1 = n1.getReal();
	double a2 = n2.getReal();
	double b1 = n1.getImaginary();
	double b2  = n2.getImaginary();

	return ComplexNumber(a1*a2 + b1*b2, b1*a2-a1*b2) ;
}

ComplexNumber  ComplexNumber::operator *(const ComplexNumber& n2)
{
	double radius = getRadius() * n2.getRadius();
	double angle = getAngle() + n2.getAngle();

	return ComplexNumber(radius * cos(angle), radius * sin(angle));
}