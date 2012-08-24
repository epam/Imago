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

import java.awt.Component;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Scanner;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Sketcher {
    private String mol;
    private static String marvinbeansPath = null;
    private static final String sketchPaneClassName = "chemaxon.marvin.beans.MSketchPane";
    private Class sketchPaneClass = null;
    private Component sketchPane;
    private Method setMolMethod;
    private JFrame parentFrame;
    //private static final String molImporterClassName = "chemaxon.formats.MolImporter";
    //private static final String moleculeClassName = "chemaxon.struc.Molecule";
    //private Class molImporterClass;
    //private Class moleculeClass;
    
    private class SketcherRunException extends Exception {
        public SketcherRunException(Exception e) {
            super(e);
        }

        public SketcherRunException(String s) {
            super(s);
        }
    }
    public Sketcher(JFrame parentFrame, String molecule) {
        this.mol = molecule;
        this.parentFrame = parentFrame;

        run();
    }

    private void run() {
        try {
            try {
                if (sketchPaneClass == null)
                    loadClasses();

                setMolMethod.invoke(sketchPane, new Object[] {mol});

                showSketcher();
            } catch (IllegalAccessException e) {
                throw new SketcherRunException(e);
            } catch (InvocationTargetException e) {
                throw new SketcherRunException(e);
            } catch (ClassNotFoundException e) {
                throw new SketcherRunException(e);
            } catch (IllegalArgumentException e) {
                throw new SketcherRunException(e);
            } catch (InstantiationException e) {
                throw new SketcherRunException(e);
            } catch (MalformedURLException e) {
                throw new SketcherRunException(e);
            } catch (NoSuchMethodException e) {
                throw new SketcherRunException(e);
            }
        } catch (SketcherRunException e) {
            int n = JOptionPane.showConfirmDialog(parentFrame,
                                "Cannot start MarvinSketch.\nWould you like to change path to its libs?",
                                "Error",
                                JOptionPane.YES_NO_OPTION);
            if (n == JOptionPane.YES_OPTION) {
                try {
                    findMarvin(false);
                    run();
                } catch (SketcherRunException se) {
                }
            }
        }
    }

    private void showSketcher() {
        JDialog sketcherDialog = new JDialog(parentFrame, true);
        sketcherDialog.setTitle("MarvinSketch");
        sketcherDialog.setLocation(parentFrame.getLocation());
        sketcherDialog.setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        sketcherDialog.add(sketchPane);
        sketcherDialog.pack();
        sketcherDialog.setVisible(true);
    }

    private void choosePath() {
        JFileChooser jfc = new JFileChooser(".");
        jfc.setDialogTitle("Specify path to MarvinBeans.jar and aloe.jar");
        jfc.setFileFilter(new FileNameExtensionFilter("JAR", "jar"));
        jfc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
        if (jfc.showOpenDialog(parentFrame) == JFileChooser.APPROVE_OPTION) {
            File f = jfc.getSelectedFile();
            if (f.isDirectory()) {
                marvinbeansPath = f.getAbsolutePath();
            } else {
                marvinbeansPath = f.getParentFile().getAbsolutePath();
            }

            try {
                FileWriter w = new FileWriter("ego.cfg");
                w.write(marvinbeansPath);
                w.flush();
            } catch (IOException e) {
            }
        }
    }

    private void findMarvin(boolean read) throws SketcherRunException {
        if (!read) {
            choosePath();
        }
        else {
            File f = new File("ego.cfg"); //TODO: in registry for windows
            if (!f.exists()) {
                choosePath();
            } else {
                try {
                    Scanner s = new Scanner(f);
                    marvinbeansPath = s.nextLine();
                } catch (FileNotFoundException e) {
                }
            }
        }
    }

    private URL[] getURLS() throws MalformedURLException {
        String[] filenames = {marvinbeansPath + "/MarvinBeans.jar", marvinbeansPath + "/aloe.jar"};
        URL[] urls = new URL[filenames.length];
        for (int i = 0; i < filenames.length; i++) {
            urls[i]= new File(filenames[i]).toURI().toURL();
        }
        return urls;
    }

    private void loadClasses() throws ClassNotFoundException, 
                                      IllegalAccessException,
                                      InstantiationException,
                                      MalformedURLException,
                                      NoSuchMethodException,
                                      SketcherRunException {
        if (marvinbeansPath == null)
            findMarvin(true);
        URL[] jars = getURLS();
        URLClassLoader ucl = new URLClassLoader(jars);

        sketchPaneClass = ucl.loadClass(sketchPaneClassName);
        sketchPane = (Component) sketchPaneClass.newInstance();

        setMolMethod = sketchPaneClass.getMethod("setMol", new Class[]{String.class});
    }
}
