/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.gga;

import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.SystemFlavorMap;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.StringReader;

/**
 *
 * @author fzentsev
 */
public class MoleculeSelection implements Transferable, ClipboardOwner {

        private String molecule;
        private DataFlavor data_flavor[] = 
               new DataFlavor[]{ DataFlavor.stringFlavor };

        private static DataFlavor extra_flavor;

        public MoleculeSelection(String mol) {

            try
            {
                extra_flavor = new DataFlavor("chemical/x-mdl-molfile");
            }
            catch(ClassNotFoundException classnotfoundexception) { }
            
            registerNativeNames("MDL_MOL");
            
            molecule = new String();
            /*String S[] = mol.split("\n");

            StringBuilder st = new StringBuilder(molecule);
            for (String s : S) {
                if (s.length() != 0) {
                    st.append(s.length());
                    st.append(s);
                }
            }

            molecule = st.toString();*/

            ByteArrayOutputStream bytearrayoutputstream = new ByteArrayOutputStream();
            int i = 0;
            for(int j = 0; j < mol.length(); j++)
            {
                char c = mol.charAt(j);
                if(c != '\n' && c != '\r')
                    continue;
                bytearrayoutputstream.write(j - i);
                for(int l = i; l < j; l++)
                    bytearrayoutputstream.write(mol.charAt(l));

                if(j < mol.length() - 1)
                {
                    char c1 = mol.charAt(j + 1);
                    if((c1 == '\n' || c1 == '\r') && c1 != c)
                        j++;
                }
                i = j + 1;
            }

            if(i < mol.length())
            {
                bytearrayoutputstream.write(mol.length() - i);

                for(int k = i; k < mol.length(); k++)
                    bytearrayoutputstream.write(mol.charAt(k));
            }

            molecule = bytearrayoutputstream.toString();
        }

        public void registerNativeNames( String name ) {

            SystemFlavorMap systemflavormap = (SystemFlavorMap)SystemFlavorMap.getDefaultFlavorMap();
            
            systemflavormap.addUnencodedNativeForFlavor(extra_flavor, name);
            systemflavormap.addFlavorForUnencodedNative(name, extra_flavor);
        }

        @Override
        public DataFlavor[] getTransferDataFlavors() {
            DataFlavor[] new_ar = new DataFlavor[2];

            new_ar[0] = data_flavor[0];
            new_ar[1] = extra_flavor;
            return new_ar;
        }

        @Override
        public boolean isDataFlavorSupported(DataFlavor flavor) {

            if (!flavor.equals(data_flavor[0]) && !flavor.equals(extra_flavor)) {
                return false;
            }
            return true;
        }

        @Override
        public Object getTransferData(DataFlavor flavor)
                throws UnsupportedFlavorException, IOException {
            if (flavor.equals(DataFlavor.stringFlavor)) {
                return molecule;
            }
            else {
                return new ByteArrayInputStream(molecule.getBytes());
            }
	} 

        @Override
        public void lostOwnership(Clipboard clipboard, Transferable contents) {
            //throw new UnsupportedOperationException("Not supported yet.");
        }
    }
