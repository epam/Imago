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

package com.ggasoftware.DocumentHandling;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;

public interface Document {

    public interface DocumentPageAsImage {
        public void paint(Graphics g);
        public BufferedImage getSelectedRectangle(Rectangle rect,
                ImageObserver observer);

        public void setScale(double scale);
        public Dimension getSize();
        public Dimension getUnscaledSize();
    }

    public int getPageCount();
    public DocumentPageAsImage getPage(int page, ImageObserver observer);
}
