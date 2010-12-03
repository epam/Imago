
package com.gga;

import java.io.File;

public class IsmilesHelper {

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

    public String getiSMILESPath( String path ) {

        path = path + File.separator + _dllpath;

        String fullpath = path;
        try {
            fullpath = (new File(path)).getCanonicalPath();
        } catch (Exception e) {
        }

        if (_os == OS_LINUX) {
            return fullpath + File.separator + "libismiles_c.so";
        } else if (_os == OS_MACOS) {
            return fullpath + File.separator + "libismiles_c.dylib";
        } else // _os == OS_WINDOWS
        {
            return fullpath + File.separator + "ismiles_c.dll";
        }
    }
}
