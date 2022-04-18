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
 * @file   exception.h
 *
 * @brief  Declares Exception class
 */

#pragma once

#include <cstdarg>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <string>

#include "comdef.h"

namespace imago
{
    class ImagoException : public std::runtime_error
    {
    public:
        ImagoException(const std::string& error) : std::runtime_error(error)
        {
        }
        ImagoException(int errorCode) : std::runtime_error(str(errorCode))
        {
        }

        static std::string str(int x)
        {
            char buffer[32];
            sprintf(buffer, "%i", x);
            return buffer;
        }
    };

    class OutOfBoundsException : public ImagoException
    {
    public:
        OutOfBoundsException(const std::string& error, int index1, int index2) : ImagoException(error + " index(" + str(index1) + ", " + str(index2) + ")")
        {
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
        LogicException(const int errorCode) : ImagoException("code: " + str(errorCode))
        {
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
}
