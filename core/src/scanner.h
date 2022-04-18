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

#include "comdef.h"

namespace imago
{
    class Scanner
    {
    public:
        virtual ~Scanner();

        virtual void read(int length, void* res) = 0;
        virtual void skip(int n) = 0;
        virtual bool isEOF() = 0;
        virtual int lookNext() = 0;
        virtual void seek(int pos, int from) = 0;
        virtual int length() = 0;
        virtual int tell() = 0;

        virtual byte readByte();
        virtual void readAll(std::string& arr);

        void readBinaryString(std::string& out);
        void readString(std::string& out, bool append_zero);

        char readChar();
        word readBinaryWord();
        int readBinaryInt();
        dword readBinaryDword();
        float readBinaryFloat();
        double readBinaryDouble();
        short readPackedShort();

        bool skipString();
        void readCharsFix(int n, char* chars_out);
        void skipSpace();

        double readDouble();
        bool tryReadDouble(double& value);
        int readInt();
        int readInt1();
        int readUnsigned();

        // when delimiters = 0, any isspace() character is considered delimiter
        void readWord(std::string& word, const char* delimiters);

        static bool isSingleLine(Scanner& scanner);
    };

    class FileScanner : public Scanner
    {
    public:
        explicit FileScanner(const char* format, ...);
        virtual ~FileScanner();

        virtual void read(int length, void* res);
        virtual bool isEOF();
        virtual void skip(int n);
        virtual int lookNext();
        virtual void seek(int pos, int from);
        virtual int length();
        virtual int tell();

    private:
        FILE* _file;
        int _file_len;

        // no implicit copy
        FileScanner(const FileScanner&);
    };

    class BufferScanner : public Scanner
    {
    public:
        explicit BufferScanner(const char* buffer, int buffer_size);
        explicit BufferScanner(const byte* buffer, int buffer_size);
        explicit BufferScanner(const char* str);
        explicit BufferScanner(const std::string& arr);

        virtual bool isEOF();
        virtual void read(int length, void* res);
        virtual void skip(int n);
        virtual int lookNext();
        virtual void seek(int pos, int from);
        virtual int length();
        virtual int tell();
        virtual byte readByte();

        const void* curptr();

    private:
        const char* _buffer;
        int _size;
        int _offset;

        void _init(const char* buffer, int length);

        // no implicit copy
        BufferScanner(const BufferScanner&);
    };
}
