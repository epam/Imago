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

#include "output.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "comdef.h"
#include "exception.h"

using namespace imago;

Output::Output()
{
}

void Output::writeByte(byte value)
{
    write(&value, sizeof(byte));
}

void Output::writeChar(char value)
{
    write(&value, sizeof(char));
}

void Output::writeBinaryDouble(double value)
{
    write(&value, sizeof(double));
}

void Output::writeBinaryInt(int value)
{
    write(&value, sizeof(int));
}

void Output::writeString(const char* string)
{
    int n = (int)strlen(string);

    write(string, n);
}

void Output::writeBinaryString(const char* string)
{
    writeString(string);
    writeByte(0);
}

void Output::writeCR()
{
    writeChar('\n');
}

void Output::writeStringCR(const char* string)
{
    writeString(string);
    writeCR();
}

void Output::printf(const char* format, ...)
{
    va_list args;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void Output::vprintf(const char* format, va_list args)
{
    char str[MAX_TEXT_LINE];
    int n = vsnprintf(str, sizeof(str), format, args);

    write(str, n);
}

void Output::skip(int count)
{
    seek(count, SEEK_CUR);
}

Output::~Output()
{
}

FileOutput::FileOutput()
{
    _f = 0;
}

FileOutput::FileOutput(const char* format, ...)
{
    char filename[MAX_TEXT_LINE];

    va_list args;

    va_start(args, format);
    vsnprintf(filename, sizeof(filename), format, args);
    va_end(args);

    _f = fopen(filename, "wb");

    if (_f == NULL)
        throw FileNotFoundException(filename);
}

void FileOutput::write(const void* data, int size)
{
    if (!_f)
        throw LogicException("FileOutput isn't opened");

    if (size < 1)
        return;

    size_t res = fwrite(data, size, 1, _f);

    if (res == 0)
        throw IOException("file writing error");
}

void FileOutput::seek(int offset, int from)
{
    if (!_f)
        throw LogicException("FileOutput isn't opened");

    fseek(_f, offset, from);
}

int FileOutput::tell()
{
    if (!_f)
        throw LogicException("FileOutput isn't opened");

    return ftell(_f);
}

void FileOutput::flush()
{
    fflush(_f);
}

void FileOutput::reopen(const char* format, ...)
{
    char filename[MAX_TEXT_LINE];

    va_list args;

    va_start(args, format);
    vsnprintf(filename, sizeof(filename), format, args);
    va_end(args);

    if (_f)
        fclose(_f);

    _f = fopen(filename, "wb");

    if (_f == NULL)
        throw FileNotFoundException("can't open file " + std::string(filename));
}

FileOutput::~FileOutput()
{
    if (_f)
        fclose(_f);
}

ArrayOutput::ArrayOutput(std::string& arr) : _buf(arr)
{
    _buf.clear();
}

void ArrayOutput::write(const void* data, int size)
{
    size_t old_size = _buf.size();

    _buf.resize(old_size + size);

    for (size_t i = 0; i < size; i++)
        _buf[i + old_size] = *((byte*)data + i);
}

void ArrayOutput::seek(int offset, int from)
{
    throw ImagoException("no seek in Array Output");
}

int ArrayOutput::tell()
{
    return (int)_buf.size();
}

ArrayOutput::~ArrayOutput()
{
}

StandardOutput::StandardOutput()
{
    _pos = 0;
}

void StandardOutput::write(const void* data, int size)
{
    int ret_size = (int)fwrite(data, size, 1, stdout);

    if (ret_size != 1)
        throw IOException("error writing in standard output");

    _pos += size;
}

void StandardOutput::seek(int offset, int from)
{
    throw LogicException("no seek in standard output");
}

int StandardOutput::tell()
{
    return _pos;
}

StandardOutput::~StandardOutput()
{
}
