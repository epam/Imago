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

#ifndef _molfile_saver_h
#define _molfile_saver_h

#include <cstdio>

namespace imago
{
    class Molecule;
    class Output;

    class MolfileSaver
    {
    public:
        MolfileSaver( Output &out );
        void saveMolecule( const Molecule &mol );
        ~MolfileSaver();
    private:
        MolfileSaver( const MolfileSaver &);
        void _writeHeader();
        void _writeCtab();
        const Molecule *_mol;
        Output &_out;
    };
}


#endif /* _molfile_saver_h */

