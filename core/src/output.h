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

#pragma once

#include <cstdarg>
#include <cstdio>
#include <string>

#include "stl_fwd.h"

namespace imago
{
    class Output
    {
    public:
        explicit Output();
        virtual ~Output();

        virtual void write(const void* data, int size) = 0;
        virtual void seek(int offset, int from) = 0;
        virtual int tell() = 0;

        void writeByte(byte value);
        void writeChar(char value);
        void writeBinaryDouble(double value);
        void writeBinaryInt(int value);
        void writeBinaryString(const char* string);

        void writeString(const char* string);
        void writeStringCR(const char* string);
        void writeCR();

        void printf(const char* format, ...);
        void vprintf(const char* format, va_list args);
        void skip(int count);
    };

    class FileOutput : public Output
    {
    public:
        FileOutput();
        explicit FileOutput(const char* format, ...);
        virtual ~FileOutput();

        void reopen(const char* format, ...);
        void flush();

        virtual void write(const void* data, int size);
        virtual void seek(int offset, int from);
        virtual int tell();

    private:
        FILE* _f;
    };

    class ArrayOutput : public Output
    {
    public:
        explicit ArrayOutput(std::string& arr);
        virtual ~ArrayOutput();

        virtual void write(const void* data, int size);
        virtual void seek(int offset, int from);
        virtual int tell();

    private:
        std::string& _buf;
    };

    class StandardOutput : public Output
    {
    public:
        StandardOutput();
        virtual ~StandardOutput();

        virtual void write(const void* data, int size);
        virtual void seek(int offset, int from);
        virtual int tell();

    private:
        int _pos;
    };
}
