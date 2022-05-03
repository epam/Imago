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

#include "molfile_saver.h"

#include <ctime>
#include <map>

#include "label_combiner.h"
#include "log_ext.h"
#include "molecule.h"
#include "output.h"
#include "settings.h"
#include "skeleton.h"
#include "superatom.h"

using namespace imago;

MolfileSaver::MolfileSaver(Output& out) : _mol(0), _out(out)
{
}

MolfileSaver::~MolfileSaver()
{
}

void MolfileSaver::saveMolecule(const Settings& vars, const Molecule& mol)
{
    _mol = &mol;

    _writeHeader();
    _writeCtab(vars);
    _out.writeStringCR("M  END");
}

void MolfileSaver::_writeHeader()
{
    time_t tm = time(NULL);
    const struct tm* lt = localtime(&tm);

    _out.writeCR();
    _out.printf("  -IMAGO- %02d%02d%02d%02d%02d2D\n", lt->tm_mon + 1, lt->tm_mday, lt->tm_year % 100, lt->tm_hour, lt->tm_min);
    _out.writeCR();
    _out.printf("%3d%3d%3d%3d%3d%3d%3d%3d%3d%3d%3d V3000\n", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void MolfileSaver::_writeCtab(const Settings& vars)
{
    logEnterFunction();

    /*const*/ Skeleton::SkeletonGraph& graph = const_cast<Skeleton::SkeletonGraph&>(_mol->getSkeleton());
    const Molecule::ChemMapping& labels = _mol->getMappedLabels();
    std::map<Skeleton::Vertex, int> mapping;

    getLogExt().appendSkeleton(vars, "Molfile saver skeleton", graph);

    _out.writeStringCR("M  V30 BEGIN CTAB");
    _out.printf("M  V30 COUNTS %d %d 0 0 0\n", graph.vertexCount(), graph.edgeCount());
    _out.writeStringCR("M  V30 BEGIN ATOM");

    int i = 1, j;
    char label[3] = {0, 0, 0};
    double bond_length;
    double capital_height;
    double capital_width;

    bond_length = vars.dynamic.AvgBondLength;
    capital_height = vars.dynamic.CapitalHeight;
    if (capital_height < 0.0)
        capital_height = 32.0;
    capital_width = capital_height * vars.labels.ratioCapital;

    for (Skeleton::SkeletonGraph::vertex_iterator begin = graph.vertexBegin(), end = graph.vertexEnd(); begin != end; begin = end)
        for (Skeleton::SkeletonGraph::vertex_descriptor v; begin != end ? (v = *begin, true) : false; ++begin)
        {
            _out.printf("M  V30 %d ", i);
            mapping[v] = i;
            Molecule::ChemMapping::const_iterator it = labels.find(v);

            const Superatom* satom;

            if (it == labels.end())
            {
                satom = 0;
                label[0] = 'C';
                label[1] = 0;
                _out.printf("%s", label);
            }
            else
            {
                satom = &(it->second->satom);

                if (satom->atoms.size() == 1)
                {
                    Atom atom = satom->atoms[0];
                    label[0] = atom.getLabelFirst();
                    label[1] = atom.getLabelSecond();
                    _out.printf("%s", label);

                    if (atom.count > 1)
                    {
                        _out.printf("%d", atom.count);
                    }

                    getLogExt().append("Label", label);

                    // R-groups used different store notation
                    if (atom.getLabelFirst() == 'R' && atom.getLabelSecond() == 0)
                    {
                        if (atom.charge > 0)
                        {
                            getLogExt().append("R-group index", atom.charge);
                            _out.printf("%d", atom.charge);
                        }
                        else
                        {
                            getLogExt().appendText("R-group index=1");
                            _out.printf("#");
                        }
                    }
                }
                else
                {
                    for (j = 0; j != satom->atoms.size(); j++)
                    {
                        const Atom& atom = satom->atoms[j];

                        if (atom.isotope > 0)
                        {
                            _out.printf("\\S%d", atom.isotope);
                        }
                        label[0] = atom.getLabelFirst();
                        label[1] = atom.getLabelSecond();
                        _out.printf("%s", label);
                        if (atom.count > 1)
                        {
                            _out.printf("%d", atom.count);
                        }
                        if (atom.getLabelFirst() == 'R' && atom.getLabelSecond() == 0 && atom.charge != 0)
                        {
                            _out.printf("\\S%d", atom.charge);
                        }
                        else
                        {
                            if (atom.charge > 0)
                            {
                                _out.printf("\\S%d+", atom.charge);
                            }
                            else if (atom.charge < 0)
                            {
                                _out.printf("\\S%d-", -atom.charge);
                            }
                        }
                    }
                }
            }

            Vec2d vert_pos = graph.getVertexPosition(v);

            if (!satom)
                _out.printf(" %lf %lf 0 0", vert_pos.x / bond_length, -vert_pos.y / bond_length);
            else
            {
                const Label& l = *(labels.find(v))->second;

                if (graph.getDegree(v) != 1)
                    _out.printf(" %lf %lf 0 0", vert_pos.x / bond_length, -vert_pos.y / bond_length);
                else
                {
                    std::deque<Skeleton::Vertex> neighbors;
                    Skeleton::SkeletonGraph::adjacency_iterator b_e, e_e;
                    b_e = graph.adjacencyBegin(v);
                    e_e = graph.adjacencyEnd(v);
                    neighbors.assign(b_e, e_e);

                    Vec2d p1 = graph.getVertexPosition(v);
                    Vec2d p2 = graph.getVertexPosition(neighbors[0]);

                    Vec2d orient;
                    orient.diff(p1, p2);
                    orient.scale((0.75 * capital_height + orient.norm()) / orient.norm());
                    p2.add(orient);

                    _out.printf(" %lf %lf 0 0", p2.x / bond_length, -p2.y / bond_length);
                }

                if (satom->atoms.size() == 1)
                {
                    if (satom->atoms[0].charge != 0 && satom->atoms[0].getLabelFirst() != 'R')
                        _out.printf(" CHG=%d", satom->atoms[0].charge);
                    if (satom->atoms[0].isotope > 0)
                        _out.printf(" MASS=%d", satom->atoms[0].isotope);
                }
            }

            _out.writeCR();
            i++;
        }

    _out.writeStringCR("M  V30 END ATOM");
    _out.writeStringCR("M  V30 BEGIN BOND");

    j = 1;
    for (Skeleton::SkeletonGraph::edge_iterator begin = graph.edgeBegin(), end = graph.edgeEnd(); begin != end; begin = end)
        for (Skeleton::SkeletonGraph::edge_descriptor e; begin != end ? (e = *begin, true) : false; ++begin)
        {
            int type;
            const Bond bond = graph.getEdgeBond(e);

            type = bond.type;

            int begin = mapping.find(e.m_source)->second, end = mapping.find(e.m_target)->second;

            if (type == BT_SINGLE_DOWN || type == BT_SINGLE_UP)
                _out.printf("M  V30 %d %d %d %d", j++, BT_SINGLE, begin, end);
            else
                _out.printf("M  V30 %d %d %d %d", j++, type, begin, end);

            // line endings "\n" here are platform-indepent and fixed.

            switch (type)
            {
            case BT_SINGLE_UP:
                _out.printf(" CFG=1\n");
                break;
            case BT_SINGLE_DOWN:
                _out.printf(" CFG=3\n");
                break;
            default:
                _out.printf("\n");
                break;
            }
        }
    _out.writeStringCR("M  V30 END BOND");
    _out.writeStringCR("M  V30 END CTAB");
}
