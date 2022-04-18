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

package com.epam.DocumentHandling;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class ImageDocument implements Document {

    private class ImagePage implements DocumentPageAsImage {

        private BufferedImage origImage;
        private BufferedImage image;
        private double scl;

        public ImagePage(BufferedImage img) {
            
            //TODO: Not sure if this right in all cases.
            if (img.getAlphaRaster() != null) {
                BufferedImage tmp = new BufferedImage(img.getWidth(), 
                        img.getHeight(), BufferedImage.TYPE_3BYTE_BGR);
                
                tmp.getGraphics().drawImage(img, 0, 0, Color.white, null);
                img = tmp;
            }
            
            scl = -1;

            origImage = img;
            image = origImage;
        }

        public Dimension getSize() {
            return new Dimension(image.getWidth(), image.getHeight());
        }

        public Dimension getUnscaledSize() {
            return new Dimension(origImage.getWidth(), origImage.getHeight());
        }

        public void paint(Graphics g) {
            if (image != null) {
                g.drawImage(image, 0, 0, null);
                g.setColor(Color.black);
                g.drawRect(-1, -1, image.getWidth() + 1, image.getHeight() + 1);
            }
        }

        public void setScale(double scale) {
            if (Math.abs(scl - scale) > 0.001 || scl == -1)
            {
                int newWidth = (int)(origImage.getWidth() * scale);
                int newHeight = (int)(origImage.getHeight() * scale);


                Image scaled = origImage.getScaledInstance(newWidth, newHeight,
                        Image.SCALE_FAST);
                image = new BufferedImage(scaled.getWidth(null), scaled.getHeight(null),
                        origImage.getType());
                image.getGraphics().drawImage(scaled, 0, 0, null);
                
                scl = scale;
            }
        }

        public BufferedImage getSelectedRectangle(Rectangle rect, ImageObserver observer) {
            return image.getSubimage(rect.x, rect.y, rect.width, rect.height);
        }

    }

    ImagePage ipage;

    public ImageDocument(File file) {
        try {
            ipage = new ImagePage(ImageIO.read(file));
        } catch (IOException e) {
        }
    }

    public ImageDocument(BufferedImage img) {
        ipage = new ImagePage(img);
    }

    public int getPageCount() {
        return 1;
    }

    public DocumentPageAsImage getPage(int page, ImageObserver observer) {
        return ipage;
    }


}
