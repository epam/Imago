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

import com.ggasoftware.DocumentHandling.Document;

import java.awt.*;
import javax.swing.*;

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
    }
    
    public void setDocument(Document document) {
        final Document doc = document;
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                jDocumentPanel.setDocument(doc);
            }
        });

        selectTab("Document");
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
        JOptionPane.showMessageDialog(this, "Unfortunately, Imago couldn't recognize selected image.", "Result",
                JOptionPane.INFORMATION_MESSAGE);
    }

    public boolean setMolecule(String molecule) {
        selectTab("Molecule");
        return jMoleculePanel.setMolecule(molecule);
    }

    public void selectTab(String title) {
        int index = jMainTabbedPane.indexOfTab(title);
        jMainTabbedPane.setEnabledAt(index, true);
        jMainTabbedPane.setSelectedIndex(index);
    }

    public void enableTab(String title) {
        int index = jMainTabbedPane.indexOfTab(title);
        jMainTabbedPane.setEnabledAt(index, true);
    }
    
    public void disableTab(String title) {
        int index = jMainTabbedPane.indexOfTab(title);
        jMainTabbedPane.setEnabledAt(index, false);
    }

    public void deleteLogTab() {
        int index = jMainTabbedPane.indexOfTab("Log");
        jMainTabbedPane.removeTabAt(index);
    }
}

