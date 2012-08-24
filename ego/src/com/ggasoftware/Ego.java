package com.ggasoftware;

import com.ggasoftware.DocumentHandling.Document;
import com.ggasoftware.DocumentHandling.ImageDocument;
import com.ggasoftware.DocumentHandling.PdfDocument;
import com.ggasoftware.DocumentHandling.TiffDocument;
import com.ggasoftware.imago.Imago;
import com.ggasoftware.imago.ImagoException;
import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.Transferable;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.image.BufferedImage;
import java.io.*;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Ego {
    private EgoFrame frame;
    private File curFile;
    private Imago imago = new Imago();
    private String molecule = "";
    private String prevSaveDirectory = ".";
    
    public Ego(String filename) {
        frame = new EgoFrame("Ego");
        setActions();
        if (filename != null) {
            setFile(new File(filename));
        }
        frame.addWindowListener(new WindowListener() {
            public void windowOpened(WindowEvent e) {}
            public void windowClosing(WindowEvent e) {
                dropLogImages();
            }
            public void windowClosed(WindowEvent e) {}
            public void windowIconified(WindowEvent e) {}
            public void windowDeiconified(WindowEvent e) {}
            public void windowActivated(WindowEvent e) {}
            public void windowDeactivated(WindowEvent e) {}
        });
    }

    public JFrame getJFrame() {
        return (JFrame)frame;
    }
    
    public void setFile(File file) {
        if (file == curFile) {
            return;
        }

        if (!Utils.checkFile(file)) {
            return;
        }

        curFile = file;
        Document doc;
        try {
            if (Utils.isPDF(file)) {
                doc = new PdfDocument(file);
            } else if (Utils.isTIF(file)) {
                doc = new TiffDocument(file);
            } else if (Utils.isAcceptableImage(file)) {
                doc = new ImageDocument(file);
            } else {
                return;
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        frame.toggleAfterRecognitionItems(false);
        frame.toggleAfterSelectionItems(false);
        frame.toggleNavigateItems(true);
        frame.setTitle("Ego: " + file.getName());

        if (Utils.isPDF(file) || Utils.isTIF(file)) {
            frame.toggleRecognizeItems(false);
        } else {
            frame.jDocumentPanel.setCareful();
            frame.toggleRecognizeItems(true);
        }
        
        frame.setDocument(doc);
    }

    public void setFileFromDialog() {
        String path = ".";
        if (curFile != null) {
            path = curFile.getParent();
        }
        JFileChooser jfc = new JFileChooser(path);
        jfc.setDialogTitle("Select document");
        jfc.setFileFilter(new FileNameExtensionFilter("Documents (png, jpg, gif"
                + ", pdf, tif, tiff)", "png", "jpg", "gif", "pdf", "tif", "tiff"));
        jfc.setFileSelectionMode(JFileChooser.FILES_ONLY);
        if (jfc.showOpenDialog(frame) == JFileChooser.APPROVE_OPTION) {
            setFile(jfc.getSelectedFile());
        }
    }

    private boolean recognitionThread() {
        BufferedImage img = frame.jDocumentPanel.getSelectedSubimage(null);
        boolean logEnabled = frame.jDocumentPanel.isLogEnabled();
        boolean result = true;

        frame.disableTab(EgoFrame.Tabs.LOG);

        try {
            if (logEnabled) {
                imago.enableLog(true);
            }
            else
                imago.disableLog();

            imago.loadImage(img);
            imago.filterImage();
            imago.recognize();
            molecule = imago.getResultMolecule();
        } catch (ImagoException ex) {
            ex.printStackTrace();
            result = false;
        }

        if (logEnabled)
            logThread();

        return result;
    }

    private void dropLogImages() {
        File f = new File("htmlimgs");
        if (f.exists()) {
            for (String child : f.list()) {
                new File("htmlimgs", child).delete();
            }
        }
        f.delete();
    }

    public void logThread() {
        Imago.LogRecord[] log = imago.getLogRecords();

        dropLogImages();
        new File("htmlimgs").mkdir();
        for (int i = 1; i < log.length; ++i) {
            try {
                FileOutputStream fos = new FileOutputStream(new File(log[i].filename));
                fos.write(log[i].data);
                fos.close();
            } catch (IOException ex) {
            }
        }

        frame.logArea.setText(new String(log[0].data));
        frame.enableTab(EgoFrame.Tabs.LOG);
    }

    public void recognize() {
        frame.selectTab(EgoFrame.Tabs.MOLECULE);
        
        final JDialog waitingDialog = new JDialog(frame, "Please wait", 
                Dialog.ModalityType.DOCUMENT_MODAL);
        
        waitingDialog.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
        waitingDialog.add(new WaitingPanel());
        waitingDialog.pack();
        Point loc = frame.getLocation();
        Dimension fdim = frame.getSize(),
                  ddim = waitingDialog.getSize();
        loc.x = loc.x + fdim.width / 2 - ddim.width / 2;
        loc.y = loc.y + fdim.height / 2 - ddim.height / 2;
        waitingDialog.setLocation(loc);
        
        Thread t = new Thread(new Runnable() {
            public void run() {
                if (!recognitionThread()
                        || !frame.setMolecule(molecule)) {
                    frame.showNoResultMessage();
                }

                frame.toggleAfterRecognitionItems(true);
                waitingDialog.dispose();
            }
        });
        t.start();
        waitingDialog.setVisible(true);      
    }    

    public void saveMolecule() {
        JFileChooser jfc = new JFileChooser(prevSaveDirectory);
        jfc.setFileFilter(new javax.swing.filechooser.FileNameExtensionFilter("Molfile", "mol"));
        int res = jfc.showSaveDialog(frame);

        if (res == JFileChooser.APPROVE_OPTION) {
            File file = jfc.getSelectedFile();
            prevSaveDirectory = file.getParent();

            try {
                FileWriter fw = new FileWriter(file);
                fw.write(molecule);
                fw.flush();
                fw.close();
            } catch (IOException e) {
            }
        }

    }

    public void copyToClipboard() {
        Clipboard systemClipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        Transferable a = systemClipboard.getContents(null);
        Transferable transferableMolecule = new MoleculeSelection(molecule);

        try {
            systemClipboard.setContents(transferableMolecule, null);
        }
        catch (Exception e) {
            System.out.print(e.getMessage());
        }

        a = systemClipboard.getContents(null);
    }
    
    public final void setActions() {
        ActionListener openAction = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                setFileFromDialog();
            }
        };

        ActionListener recognizeAction = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                recognize();
            }
        };
        ActionListener saveAction = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                saveMolecule();
            }
        };
        ActionListener copyAction = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                copyToClipboard();
            }
        };

        ActionListener previousDocumentAction = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.recoverPreviousDocument();
                frame.jMainTabbedPane.setSelectedIndex(0);
            }
        };

        ActionListener sketcherAction = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    new Sketcher(frame, frame.jMoleculePanel.getMoleculeString());
                } catch (java.lang.UnsatisfiedLinkError ex) {
                }
            }
        };

        frame.jOpenButton.addActionListener(openAction);
        frame.jRecognizeButton.addActionListener(recognizeAction);
        frame.jSaveButton.addActionListener(saveAction);
        frame.jCopyButton.addActionListener(copyAction);
        frame.jPreviousDocumentButton.addActionListener(previousDocumentAction);
        frame.jSketcherButton.addActionListener(sketcherAction);

        frame.jQuitMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                getJFrame().dispose();
            }
        });

        frame.jOpenMenuItem.addActionListener(openAction);
        frame.jRecognizeMenuItem.addActionListener(recognizeAction);
        frame.jSaveMenuItem.addActionListener(saveAction);
        frame.jCopyMenuItem.addActionListener(copyAction);

        frame.jFirstPageMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.setFirstPage();
            }
        });

        frame.jNextPageMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.setNextPage();
            }
        });
        frame.jPreviousPageMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.setPrevPage();
            }
        });

        frame.jLastPageMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.setLastPage();
            }
        });

        frame.jZoomInMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.increaseScale();
            }
        });

        frame.jZoomOutMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.decreaseScale();
            }
        });

        frame.jActualSizeMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.setActualSize();
            }
        });

        frame.jFitWidthMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.fitWidth();
            }
        });

        frame.jFitHeightMenuItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.jDocumentPanel.fitHeight();
            }
        });

        frame.jPreviousDocumentMenuItem.addActionListener(previousDocumentAction);
        frame.jSketcherMenuItem.addActionListener(sketcherAction);
    }

    private static void setupUI() {
        try {
            String os = System.getProperty("os.name");
            if (os.indexOf("Linux") >= 0) {
                UIManager.LookAndFeelInfo infos[] = UIManager.getInstalledLookAndFeels();

                for (int i = 0; i != infos.length; i++) {
                    if (infos[i].getName().equals("Nimbus")) {
                        UIManager.setLookAndFeel(infos[i].getClassName());
                        return;
                    }
                }
            }

            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
        }
    }
    
    public static void main(String args[]) {
        setupUI();

        String filename = null;
        if (args.length > 0) {
            filename = args[0];
        }

        new Ego(filename);
    }
}
