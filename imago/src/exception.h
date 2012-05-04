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

/**
  * @file   exception.h
  * 
  * @brief  Declares Exception class
  */

#ifndef _exception_h
#define _exception_h

#include <cstdarg>
#include <cstdio>
#include <exception>

#include "comdef.h"

class ImagoException : public std::exception
{
public: 
	ImagoException(const std::string& problemDescription) : std::exception(problemDescription.c_str())
	{
	}
};

class OutOfBoundsException : public ImagoException
{
public:
	OutOfBoundsException(const std::string& method, int index1, int index2)
		: ImagoException(method)
	{
		// TODO
	}
};

class NoContourException : public ImagoException
{
public: 
	NoContourException(const std::string& error) : ImagoException(error)
	{
	}
};

class LabelException : public ImagoException
{
public: 
	LabelException(const std::string& error) : ImagoException(error)
	{
	}
};

class FileNotFoundException : public ImagoException
{
public: 
	FileNotFoundException(const std::string& error) : ImagoException(error)
	{
	}
};

class LogicException : public ImagoException
{
public: 
	LogicException(const std::string& error) : ImagoException(error)
	{
	}

	LogicException(const int errorCode) : ImagoException("TODO")
	{
		// TODO!
	}
};

class IOException : public ImagoException
{
public: 
	IOException(const std::string& error) : ImagoException(error)
	{
	}
};

class DivizionByZeroException : public ImagoException
{
public: 
	DivizionByZeroException(const std::string& error) : ImagoException(error)
	{
	}
};

class OCRException : public ImagoException
{
public: 
	OCRException(const std::string& error) : ImagoException(error)
	{
	}
};

#endif /* _exception_h */
