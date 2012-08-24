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

package com.ggasoftware;

import com.ggasoftware.DocumentHandling.Document;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class EgoFrame extends EgoForm {
    
    public EgoFrame(String name) {
        super(name);        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        new FormBuilder(this).build();
        new MenuBuilder(this).build();
        
        pack();
        
        Dimension screen_size = Toolkit.getDefaultToolkit().getScreenSize();

        setLocation((screen_size.width - getWidth()) / 2,
                    (screen_size.height - getHeight()) / 2);
        
        
        setVisible(true);
        jDocumentPanel.setParent(this);

        jMainTabbedPane.setEnabledAt(0, false);
        jMainTabbedPane.setEnabledAt(1, false);
        jMainTabbedPane.setEnabledAt(2, false);
               
        jNoResultPanel = new JPanel(new BorderLayout());
        jNoResultLabel = new JLabel("Unfortunately, Imago couldn't recognize selected image.", JLabel.CENTER);
        jNoResultPanel.add(jNoResultLabel, BorderLayout.CENTER);        
    }
    
    public void setDocument(Document document) {
        final Document doc = document;
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                jDocumentPanel.setDocument(doc);
            }
        });

        selectTab(EgoFrame.Tabs.DOCUMENT);
    }
    
    public void toggleNavigateItems(boolean value) {
        jNavigateMenu.setEnabled(value);
        jZoomMenu.setEnabled(value);
    }

    public void toggleRecognizeItems(boolean value) {
        jRecognizeButton.setEnabled(value);
        jRecognizeMenuItem.setEnabled(value);
    }

    public void toggleAfterRecognitionItems(boolean value) {
        jCopyMenuItem.setEnabled(value);
        jCopyButton.setEnabled(value);

        jSaveMenuItem.setEnabled(value);
        jSaveButton.setEnabled(value);

        jSketcherMenuItem.setEnabled(value);
        jSketcherButton.setEnabled(value);
    }

    public void toggleAfterSelectionItems(boolean value) {
        jPreviousDocumentButton.setEnabled(value);
        jPreviousDocumentMenuItem.setEnabled(value);
        
        if (value == true) {
            toggleRecognizeItems(true);
        }
    }
    
    public void showNoResultMessage() {
        if (!jNoResultPanel.equals(jMainTabbedPane.getComponentAt(Tabs.LOG.index))) {
            jMainTabbedPane.setComponentAt(Tabs.LOG.index, jNoResultPanel);
        }
        selectTab(Tabs.LOG);
    }

    public boolean setMolecule(String molecule) {
        selectTab(Tabs.MOLECULE);
        return jMoleculePanel.setMolecule(molecule);
    }

    public enum Tabs {
        DOCUMENT(0),
        LOG(1),
        MOLECULE(2);
        
        public int index;
        Tabs(int index) {
            this.index = index;
        }
    }
    
    public void selectTab(Tabs tab) {
        jMainTabbedPane.setEnabledAt(tab.index, true);
        jMainTabbedPane.setSelectedIndex(tab.index);
    }
    
    public void enableTab(Tabs tab) {
        jMainTabbedPane.setEnabledAt(tab.index, true);
    }
    
    public void disableTab(Tabs tab) {
        jMainTabbedPane.setEnabledAt(tab.index, false);
    }
        
    private javax.swing.JPanel jNoResultPanel;
    private javax.swing.JLabel jNoResultLabel;
}

