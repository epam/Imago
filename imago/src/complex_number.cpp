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