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

package com.epam;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import javax.swing.JPanel;

public class ImagePanel extends javax.swing.JPanel {

    private Image orig_img = null;
    private Image scaled_img = null;

    void ImagePanel() {
    }

    private void scaleImage() {
        if (orig_img == null)
            return;

        scaled_img = null;
        
        int i_height = orig_img.getHeight(this);
        int i_width = orig_img.getWidth(this);

        if (i_height > i_width) {
            if (i_height > getHeight()) {
                scaled_img = orig_img.getScaledInstance(-1, getHeight(), Image.SCALE_FAST);
            }
        }
        else {
            if (i_width > getWidth()) {
                scaled_img = orig_img.getScaledInstance(getWidth(), -1, Image.SCALE_FAST);
            }
        }
        if (scaled_img == null)
            scaled_img = orig_img;
    }

    void setImage(Image new_img) {
        orig_img = new_img;
        scaleImage();
    }
    
    @Override
    public void paint(Graphics g) {
        super.paint(g);

        if (scaled_img != null) {
            g.drawImage(scaled_img, (getWidth() - scaled_img.getWidth(this)) / 2, (getHeight() - scaled_img.getHeight(this)) / 2, this);
        }
        else {
            g.setColor(Color.WHITE);
            g.fillRect(0, 0, getWidth(), getHeight());
        }
    }
}
