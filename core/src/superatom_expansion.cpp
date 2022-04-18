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

#include "superatom_expansion.h"

#include <indigo.h>

#include "log_ext.h"
#include "molecule.h"
#include "molfile_saver.h"
#include "output.h"

namespace imago
{

    std::string expandSuperatoms(const Settings& vars, const Molecule& molecule)
    {
        logEnterFunction();

        std::string molString;
        ArrayOutput so(molString);
        MolfileSaver ma(so);
        ma.saveMolecule(vars, molecule);

        if (!vars.general.ExpandAbbreviations)
            return molString;

        indigoSetOption("treat-x-as-pseudoatom", "true");
        indigoSetOption("ignore-stereochemistry-errors", "true");

        int mol = indigoLoadMoleculeFromString(molString.c_str());

        if (mol == -1)
        {
            fprintf(stderr, "%s\n", indigoGetLastError());
            return molString;
        }

        int expCount = indigoExpandAbbreviations(mol);
        if (expCount == -1)
        {
            fprintf(stderr, "%s\n", indigoGetLastError());
            return molString;
        }

        std::string newMolfile = indigoMolfile(mol);
        indigoFree(mol);

        return newMolfile;
    }
}
