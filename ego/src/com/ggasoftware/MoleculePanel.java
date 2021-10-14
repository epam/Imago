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

package com.ggasoftware;

import com.ggasoftware.indigo.*;
import java.awt.BorderLayout;
import java.awt.Image;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class MoleculePanel extends JPanel {
    private ImagePanel molPicture = new ImagePanel();
    private Indigo indigo = new Indigo();
    private IndigoRenderer indigo_renderer = new IndigoRenderer(indigo);
    private String molecule = "";
    public MoleculePanel() {
        indigo.setOption("render-output-format", "png");
        indigo.setOption("render-label-mode", "terminal-hetero");
        indigo.setOption("render-coloring", true);
        indigo.setOption("ignore-stereochemistry-errors", true);

        setLayout(new BorderLayout());
        add(molPicture);

        molPicture.addComponentListener(new ComponentListener() {
            @Override
            public void componentResized(ComponentEvent ce) {
                String params = ce.paramString();
                int b = params.lastIndexOf(" ");
                int e = params.lastIndexOf(")");
                params = params.substring(b + 1, e);
                String[] dims = params.split("x");
                int width = Integer.parseInt(dims[0]);
                int height = Integer.parseInt(dims[1]);
                indigo.setOption("render-image-size", width, height);
            }

            @Override
            public void componentMoved(ComponentEvent ce) {}
            @Override
            public void componentShown(ComponentEvent ce) {}
            @Override
            public void componentHidden(ComponentEvent ce) {}
        });
    }

    public void clear() {
        molecule = null;
        molPicture.setImage(null);
    }

    public String getMoleculeString() {
        return molecule;
    }
    
    public boolean setMolecule(String molecule) {
        this.molecule = molecule;
        indigo.setOption("render-background-color", 1.0f, 1.0f, 1.0f);
        IndigoObject indigo_mol = indigo.loadQueryMolecule(molecule);

        byte[] pict = indigo_renderer.renderToBuffer(indigo_mol);
        try {
            Image mol_image = ImageIO.read(new ByteArrayInputStream(pict));

            molPicture.setImage(mol_image);
            molPicture.repaint();
        } catch (IOException ex) {
            return false;
        }
        return true;
    }
}