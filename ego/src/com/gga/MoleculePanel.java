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

package com.gga;

import com.gga.indigo.*;
import java.awt.Image;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.GroupLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;

import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.SystemFlavorMap;
import java.awt.datatransfer.Transferable;

public class MoleculePanel extends JPanel {
    
    public MoleculePanel() {

        molPicture = new ImagePanel();
        settingsText = new JLabel();
        yesButton = new JButton("Yes");

        indigo = new Indigo(Ego.jarDir + File.separator + "lib");
        indigo_renderer = new IndigoRenderer(indigo);
        indigo.setOption("render-output-format", "png");
        indigo.setOption("render-label-mode", "normal");
        indigo.setOption("render-coloring", true);
        indigo.setOption("ignore-stereochemistry-errors", true);

        GroupLayout gl_p3 = new GroupLayout(this);
        setLayout(gl_p3);

        gl_p3.setAutoCreateGaps(true);

        gl_p3.setHorizontalGroup(gl_p3.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(molPicture, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                /*.addGroup(gl_p3.createSequentialGroup()
                    .addComponent(saveButton)
                    .addComponent(copyButton)
                    .addComponent(sketchButton))*/
                .addGroup(gl_p3.createSequentialGroup()
                    .addComponent(settingsText)
                    .addComponent(yesButton))
                );

        gl_p3.setVerticalGroup(gl_p3.createSequentialGroup()
                .addComponent(molPicture, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                /*.addGroup(gl_p3.createParallelGroup(GroupLayout.Alignment.CENTER)
                    .addComponent(saveButton)
                    .addComponent(copyButton)
                    .addComponent(sketchButton))*/
                .addGroup(gl_p3.createParallelGroup(GroupLayout.Alignment.CENTER)
                    .addComponent(settingsText)
                    .addComponent(yesButton))
                );

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
            public void componentMoved(ComponentEvent ce) {
            }

            @Override
            public void componentShown(ComponentEvent ce) {
            }

            @Override
            public void componentHidden(ComponentEvent ce) {
            }
        });
    }

    public void updateText(Imago imago) {
        settingsText.setText("Do you want to try with another predefined settings? " +
                '(' + (imago.currentConfigId + 1) + '/' + Imago.configsCount + ')');
    }

    public void clear() {
        mol = null;
        molPicture.setImage(null);
    }

    public void setMolecule(String molecule) throws Exception {
        mol = molecule;
        //dingo.beginLog("log.txt");
        indigo.setOption("render-background-color", 1.0f, 1.0f, 1.0f);
        IndigoObject indigo_mol = indigo.loadQueryMolecule(mol);

        byte[] pict = indigo_renderer.renderToBuffer(indigo_mol);
        //dingo.endLog();
        Image mol_image = ImageIO.read(new ByteArrayInputStream(pict));
        
        molPicture.setImage(mol_image);
        molPicture.repaint();
    }

    public void saveMolecule() {
        JFileChooser jfc = new JFileChooser(prevDirectory);
        jfc.setFileFilter(new javax.swing.filechooser.FileNameExtensionFilter("Molfile", "mol"));
        int res = jfc.showSaveDialog(this);

        if (res == JFileChooser.APPROVE_OPTION) {
            File file = jfc.getSelectedFile();
            prevDirectory = file.getParent();

            try {
                FileWriter fw = new FileWriter(file);
                fw.write(mol);
                fw.flush();
            } catch (IOException e) {
            }
        }
    }
    
    public void copyToClipboard() {

        Clipboard systemClipboard =
        Toolkit.getDefaultToolkit().getSystemClipboard();

        Transferable a = systemClipboard.getContents(null);

        Transferable transferableMolecule = new MoleculeSelection(mol);

        try {
            systemClipboard.setContents(transferableMolecule, null);
        }
        catch (Exception e) {
            System.out.print(e.getMessage());
        }

        a = systemClipboard.getContents(null);

        //try {
            
        //}
        //catch (Exception e){
          //  System.out.println(e.getMessage());
        //}
    }

    private ImagePanel molPicture;
    private JLabel settingsText;
    public JButton yesButton;
    private Indigo indigo;
    private IndigoRenderer indigo_renderer;
    public String mol = "";
    private static String prevDirectory = ".";
}