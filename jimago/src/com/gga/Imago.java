/****************************************************************************
 * Copyright (C) 2010 GGA Software Services LLC
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

import java.io.File;
import java.io.FileNotFoundException;
import java.awt.image.BufferedImage;
import java.awt.image.DataBuffer;
import java.awt.Graphics;

public class Imago {

    static public class NoResultException extends Exception {

        public NoResultException() {
            super();
        }

        public NoResultException(String str) {
            super(str);
        }
    }

    public interface ImagoLogCallback {

        public void log(String str);
    }

    public Imago(String path) {
        path = path + File.separator + _dllpath;

        String fullpath = path;
        try {
            fullpath = (new File(path)).getCanonicalPath();
        } catch (Exception e) {
        }

        if (_os == OS_LINUX) {
            System.load(fullpath + File.separator + "libimagojni.so");
        } else if (_os == OS_MACOS) {
            System.load(fullpath + File.separator + "libimagojni.dylib");
        } else // _os == OS_WINDOWS
        {
            System.load(fullpath + File.separator + "imagojni.dll");
        }

        _sid = allocSessionId();
        configsCount = getConfigsCount();
    }

    public Imago() {
        this("lib");
    }

    @Override
    protected void finalize() throws Throwable {
        releaseSessionId(_sid);
        disableLog();
    }
    public int currentConfigId = 0;
    public static int configsCount;

    public void nextConfig() throws Exception  {
        setConfig((currentConfigId + 1) % configsCount);
    }

    public void setConfig(int num) throws Exception {
        currentConfigId = num;
        setConfigNumber(num);
        //if (setConfigNumber(num) == 0)
        //    throw new Exception(getLastError());
    }
    
    public void setLogCallback(ImagoLogCallback callback) {
        logCallback = callback;
        enableLog();
    }

    public void loadPNG (String filename) throws Exception {
        loadPNGImageFromFile(filename);
    }

    public void loadPNG (byte[] buffer) throws Exception {
        loadPNGImageFromBuffer(buffer);
    }

    public void exportPNG (String filename) throws Exception {
         savePNGImageToFile(filename);
    }

    public void loadBufImage (BufferedImage image) throws Exception {
        BufferedImage img = new BufferedImage(image.getWidth(), image.getHeight(),
            BufferedImage.TYPE_BYTE_GRAY);  
        Graphics g = img.getGraphics();  
        g.drawImage(image, 0, 0, null);  
        g.dispose(); 

        DataBuffer buf = img.getData().getDataBuffer();
        byte[] simple_buf = new byte[buf.getSize()];  
        for (int j = 0; j < buf.getSize(); j++)
            simple_buf[j] = (byte)buf.getElem(j);	
            
        int w = img.getWidth(), h = img.getHeight();

        loadGreyscaleRawImage(simple_buf, w, h);	
    }

    private ImagoLogCallback logCallback = null;

    private native void enableLog();

    private native void disableLog();
    private long _sid;

    private static native long allocSessionId();

    private static native void releaseSessionId(long id);

    //private native String getLastError();

    public native int setFilter(String filter);

    public native int setBinarizationLevel(int level);

    public static native int getConfigsCount();

    private native int setConfigNumber(int num);

    public native void saveMolToFile(String filename);

    public native String getResult();

    private native void loadPNGImageFromBuffer(byte[] buf);

    public native void loadGreyscaleRawImage(byte[] buf, int w, int h);

    private native void savePNGImageToFile(String filename);
    private native void loadPNGImageFromFile(String filename);
    public native void loadAndFilterJpgFile (String filename);

    public native void recognize();

    //private static void saveMolToString(String mol);
    ////////////////////////////////////////////////////////////////
    // INITIALIZATION
    ////////////////////////////////////////////////////////////////
    private static final int OS_WINDOWS = 1;
    private static final int OS_LINUX = 2;
    private static final int OS_MACOS = 3;
    private static final int X86 = 32;
    private static final int X64 = 64;
    private static int _arch = 0;
    private static int _os = 0;
    private static String _dllpath = "";

    private static int getArch() {
        String archstr = System.getProperty("os.arch");
        if (archstr.equals("x86") || archstr.equals("i386")) {
            return X86;
        } else if (archstr.equals("x86_64") || archstr.equals("amd64")) {
            return X64;
        } else {
            throw new Error("Platform not recognized");
        }
    }

    private static int getOs() {
        String namestr = System.getProperty("os.name");
        if (namestr.matches("^Windows.*")) {
            return OS_WINDOWS;
        } else if (namestr.matches("^Mac OS.*")) {
           return OS_MACOS;
        } else if (namestr.matches("^Linux.*")) {
            return OS_LINUX;
        } else {
            throw new Error("Operating system not recognized");
        }
    }

    private static String getDllPath() {
        String path = "";
        switch (_os) {
            case OS_WINDOWS:
                path += "Win";
                break;
            case OS_LINUX:
                path += "Linux";
                break;
            case OS_MACOS:
                path += "Mac";
                break;
            default:
                throw new Error("OS not set");
        }
        path += File.separator;

        if (_os == OS_MACOS) {
            String version = System.getProperty("os.version");

            if (version.startsWith("10.5")) {
                path += "10.5";
            } else if (version.startsWith("10.6")) {
                path += "10.6";
            } else {
                throw new Error("OS version not supported");
            }
        } else {
            switch (_arch) {
                case X86:
                    path += "x86";
                    break;
                case X64:
                    path += "x64";
                    break;
                default:
                    throw new Error("Platform not set");
            }
        }

        return path;
    }

    static {
        _arch = getArch();
        _os = getOs();
        _dllpath = getDllPath();
    }
}

