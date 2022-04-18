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

package com.epam.imago;

import com.sun.jna.*;
import com.sun.jna.ptr.*;

public interface ImagoLib extends Library {
    String imagoGetVersion();
    String imagoGetLastError();

    long imagoAllocSessionId();
    void imagoSetSessionId(long id);
    void imagoReleaseSessionId(long id);
    
    int imagoSetConfig(String config);
    String imagoGetConfigsList();

    int imagoSetFilter(String filter);

    int imagoLoadImageFromBuffer(byte[] buf, int buf_size);
    int imagoLoadImageFromFile(String filename);

    int imagoSaveImageToFile(String filename);

    int imagoLoadGreyscaleRawImage(byte[] buf, int width, int height);

    int imagoSetLogging(int mode);

    int imagoRecognize(IntByReference warnings);

    int imagoSaveMolToBuffer(PointerByReference buf, IntByReference buf_size);
    int imagoSaveMolToFile(String filename);

    int imagoFilterImage();

    int imagoGetInkPercentage(DoubleByReference percentage);

    int imagoGetPrefilteredImageSize(IntByReference width, IntByReference height);
    int imagoGetPrefilteredImage(PointerByReference data, IntByReference width, IntByReference height);

    int imagoSetSessionSpecificData(Pointer data);
    int imagoGetSessionSpecificData(PointerByReference data);
    
    int imagoGetLogCount(IntByReference count);
    int imagoGetLogRecord(int it, PointerByReference name, IntByReference length, PointerByReference data);
}