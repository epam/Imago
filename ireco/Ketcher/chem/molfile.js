/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU Affero General Public License version 3 as published by the Free
 * Software Foundation and appearing in the file LICENSE.GPL included in
 * the packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

if (!window.chem || !chem.Vec2 || !chem.Molecule)
    throw new Error("Vec2 and Molecule should be defined first")

chem.Molfile = function ()
{}

chem.Molfile.parseDecimalInt = function (str)
{
    var val = parseInt(str, 10);
    
    return isNaN(val) ? 0 : val;
}

chem.Molfile.partitionLine = function (/*string*/ str, /*array of int*/ parts, /*bool*/ withspace)
{
    var res = [];
    for (var i = 0, shift = 0; i < parts.length; ++i)
    {
        res.push(str.slice(shift, shift + parts[i]));
        if (withspace)
            shift++;
        shift += parts[i];
    }
    return res;
}

chem.Molfile.partitionLineFixed = function (/*string*/ str, /*int*/ itemLength, /*bool*/ withspace)
{
    var res = [];
    for (var shift = 0; shift < str.length; shift += itemLength)
    {
        res.push(str.slice(shift, shift + itemLength));
        if (withspace)
            shift++;
    }
    return res;
}

chem.Molfile.parseMolfile = function (molfileLines, isRxn)
{
	if (isRxn)
		return chem.Molfile.parseRxn(molfileLines);
	else
		return chem.Molfile.parseCTab(molfileLines);
}

chem.Molfile.fmtInfo = {
    invRetMap: [null, "inv", "ret"],
    bondTypeMap: {
        1: chem.Molecule.BOND.TYPE.SINGLE,
        2: chem.Molecule.BOND.TYPE.DOUBLE,
        3: chem.Molecule.BOND.TYPE.TRIPLE,
        4: chem.Molecule.BOND.TYPE.AROMATIC,
        5: chem.Molecule.BOND.TYPE.SINGLE_OR_DOUBLE,
        6: chem.Molecule.BOND.TYPE.SINGLE_OR_AROMATIC,
        7: chem.Molecule.BOND.TYPE.DOUBLE_OR_AROMATIC,
        8: chem.Molecule.BOND.TYPE.ANY},
    bondStereoMap: {
        0: chem.Molecule.BOND.STEREO.NONE,
        1: chem.Molecule.BOND.STEREO.UP,
        4: chem.Molecule.BOND.STEREO.EITHER,
        6: chem.Molecule.BOND.STEREO.DOWN,
        3: chem.Molecule.BOND.STEREO.CIS_TRANS},
    v30bondStereoMap: {
        0: chem.Molecule.BOND.STEREO.NONE,
        1: chem.Molecule.BOND.STEREO.UP,
        2: chem.Molecule.BOND.STEREO.EITHER,
        3: chem.Molecule.BOND.STEREO.DOWN},
    bondTopologyMap: {
        0: chem.Molecule.BOND.TOPOLOGY.EITHER,
        1: chem.Molecule.BOND.TOPOLOGY.RING,
        2: chem.Molecule.BOND.TOPOLOGY.CHAIN},
    countsLinePartition: [3,3,3,3,3,3,3,3,3,3,3,6],
    atomLinePartition: [10,10,10,1,3,2,3,3,3,3,3,3,3,3,3,3,3],
    bondLinePartition: [3,3,3,3,3,3,3],
    atomListHeaderPartition: [3,1,1,4,1,1],
    atomListHeaderLength: 11, // = atomListHeaderPartition.reduce(function(a,b) { return a + b; }, 0)
    atomListHeaderItemLength: 4,
    chargeMap: [0, +3, +2, +1, 0, -1, -2, -3],
    valenceMap: [undefined, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0],
    implicitHydrogenMap: [undefined, 0, 1, 2, 3, 4],
    v30atomPropMap: {'CHG':'charge', 'RAD':'radical', 'MASS':'isotope', 'VAL':'valence'},
    rxnItemsPartition: [3,3,3]
}

chem.Molfile.parseAtomLine = function (atomLine)
{
    var mf = chem.Molfile;
    var atomSplit = mf.partitionLine(atomLine, mf.fmtInfo.atomLinePartition);
    var params =
        {
        // generic
        pos: new chem.Vec2(parseFloat(atomSplit[0]), parseFloat(atomSplit[1])),
        label: atomSplit[4].strip(),
        valence: mf.fmtInfo.valenceMap[mf.parseDecimalInt(atomSplit[10])],

        // obsolete
        massDifference: mf.parseDecimalInt(atomSplit[5]),
        charge: mf.fmtInfo.chargeMap[mf.parseDecimalInt(atomSplit[6])],
        
        // query
        implicitH: mf.fmtInfo.implicitHydrogenMap[mf.parseDecimalInt(atomSplit[8])],
        stereoCare: mf.parseDecimalInt(atomSplit[9]) != 0,

        // reaction
        aam: mf.parseDecimalInt(atomSplit[14]),
        invRet: mf.fmtInfo.invRetMap[mf.parseDecimalInt(atomSplit[15])],

        // reaction query
        exactChangeFlag: mf.parseDecimalInt(atomSplit[16]) != 0
        };
    params.explicitValence = typeof(params.valence) != 'undefined';
    return new chem.Molecule.Atom(params);
}

chem.Molfile.stripV30 = function (line)
{
    if (line.slice(0, 7) != 'M  V30 ')
        throw Error("Prefix invalid");
    return line.slice(7);
}

chem.Molfile.parseAtomLineV3000 = function (line)
{
    var mf = chem.Molfile;
    var split, subsplit, key, value, i;
    split = mf.spaceparsplit(line);
    var params = {
        pos: new chem.Vec2(parseFloat(split[2]), parseFloat(split[3])),
        aam: split[5].strip()
    };
	var label = split[1].strip();
	if (label.charAt(0) == "\"" && label.charAt(label.length - 1) == "\"") {
		label = label.substr(1, label.length - 2); // strip qutation marks
	}
	if (label.charAt(label.length - 1) == "]") { // assume atom list
		label = label.substr(0, label.length - 1); // remove ']'
		var atomListParams = {};
		atomListParams.notList = false;
		if (label.substr(0, 5) == "NOT [") {
			atomListParams.notList = true;
			label = label.substr(5); // remove 'NOT ['
		} else if (label.charAt(0) != "[") {
			throw "Error: atom list expected, found \'" + label + "\'";
		} else {
			label = label.substr(1); // remove '['
		}
		atomListParams.ids = mf.labelsListToIds(label.split(","));
		params['atomList'] = new chem.Molecule.AtomList(atomListParams);
		params['label'] = 'L';
	} else {
		params['label'] = label;
	}
    split.splice(0, 6);
    for (i = 0; i < split.length; ++i) {
        subsplit = mf.splitonce(split[i], '=');
        key = subsplit[0];
        value = subsplit[1];
        if (key in mf.fmtInfo.v30atomPropMap)
            params[mf.fmtInfo.v30atomPropMap[key]] = mf.parseDecimalInt(value);
    }
    params.explicitValence = typeof(params.valence) != 'undefined';
    return new chem.Molecule.Atom(params);
}

chem.Molfile.parseBondLineV3000 = function (line)
{
    var mf = chem.Molfile;
    var split, subsplit, key, value, i;
    split = mf.spaceparsplit(line);
    var params = {
        begin: mf.parseDecimalInt(split[2]) - 1,
        end: mf.parseDecimalInt(split[3]) - 1,
        type: mf.fmtInfo.bondTypeMap[mf.parseDecimalInt(split[1])]
    };
    split.splice(0, 4);
    for (i = 0; i < split.length; ++i) {
        subsplit = mf.splitonce(split[i], '=');
        key = subsplit[0];
        value = subsplit[1];
        if (key == 'CFG')
            params.stereo = mf.fmtInfo.v30bondStereoMap[mf.parseDecimalInt(value)];
        else if (key == 'TOPO')
            params.topology = mf.fmtInfo.bondTopologyMap[mf.parseDecimalInt(value)];
        else if (key == 'RXCTR')
            params.reactingCenterStatus = mf.parseDecimalInt(value);
        else if (key == 'STBOX')
            params.stereoCare = mf.parseDecimalInt(value);
    }
    return new chem.Molecule.Bond(params);
}

chem.Molfile.parseBondLine = function (bondLine)
{
    var mf = chem.Molfile;
    var bondSplit = mf.partitionLine(bondLine, mf.fmtInfo.bondLinePartition);
    var params =
        {
        begin: mf.parseDecimalInt(bondSplit[0]) - 1,
        end: mf.parseDecimalInt(bondSplit[1]) - 1,
        type: mf.fmtInfo.bondTypeMap[mf.parseDecimalInt(bondSplit[2])],
        stereo: mf.fmtInfo.bondStereoMap[mf.parseDecimalInt(bondSplit[3])],
        topology: mf.fmtInfo.bondTopologyMap[mf.parseDecimalInt(bondSplit[5])],
        reactingCenterStatus: mf.parseDecimalInt(bondSplit[6])
        };
        
    return new chem.Molecule.Bond(params);
}

chem.Molfile.parseAtomListLine = function (/* string */atomListLine)
{
    var mf = chem.Molfile;
    var split = mf.partitionLine(atomListLine, mf.fmtInfo.atomListHeaderPartition);

    var number = mf.parseDecimalInt(split[0]) - 1;
    var notList = (split[2].strip() == "T");
    var count = mf.parseDecimalInt(split[4].strip());

    var ids = atomListLine.slice(mf.fmtInfo.atomListHeaderLength);
    var list = [];
    var itemLength = mf.fmtInfo.atomListHeaderItemLength;
    for (var i = 0; i < count; ++i)
        list[i] = mf.parseDecimalInt(ids.slice(i * itemLength, (i + 1) * itemLength - 1));

    return {"aid": number, "atomList" : new chem.Molecule.AtomList({"notList": notList, "ids": list})};
}

chem.Molfile.readKeyValuePairs = function (str, /* bool */ valueString)
{
    var mf = chem.Molfile;
    var ret = {};
    var partition = mf.partitionLineFixed(str, 3, true);
    var count = mf.parseDecimalInt(partition[0]);
    for (var i = 0; i < count; ++i)
        ret[mf.parseDecimalInt(partition[2 * i + 1]) - 1] =
			valueString ? partition[2 * i + 2].strip() :
				mf.parseDecimalInt(partition[2 * i + 2]);
    return ret;
}

chem.Molfile.labelsListToIds = function (labels)
{
	var ids = [];
	for (var i = 0; i < labels.length; ++i) {
		ids.push(chem.Element.getElementByLabel(labels[i].strip()));
	}
	return ids;
}

chem.Molfile.parsePropertyLineAtomList = function (hdr, lst)
{
    var mf = chem.Molfile;
    var aid = mf.parseDecimalInt(hdr[1]) - 1;
    var count = mf.parseDecimalInt(hdr[2]);
    var notList = hdr[4].strip() != 'T';
	var ids = mf.labelsListToIds(lst.slice(0, count));
    var ret = {};
    ret[aid] = new chem.Molecule.AtomList({"notList": notList, "ids": ids});
    return ret;
}

chem.Molfile.initSGroup = function (sGroups, propData)
{
    var mf = chem.Molfile;
	var kv = mf.readKeyValuePairs(propData, true);
	for (var key in kv) {
		if (kv[key] != 'MUL')
			throw new Error('Unsupported S-group type');
		var sg = {
			'type': kv[key],
			'number': key
		};
		sGroups[key] = sg;
	}
}

chem.Molfile.applySGroupProp = function (sGroups, propName, propData, numeric)
{
    var mf = chem.Molfile;
	var kv = mf.readKeyValuePairs(propData, !(numeric));
	for (var key in kv) {
		sGroups[key][propName] = kv[key];
	}
}

chem.Molfile.toIntArray = function (strArray)
{
    var mf = chem.Molfile;
    var ret = [];
	for (var j = 0; j < strArray.length; ++j)
		ret[j] = mf.parseDecimalInt(strArray[j]);
	return ret;
}

chem.Molfile.applySGroupArrayProp = function (sGroups, propName, propData)
{
    var mf = chem.Molfile;
	var sid = mf.parseDecimalInt(propData.slice(1, 4))-1;
	var part = mf.toIntArray(mf.partitionLineFixed(propData.slice(4), 3, true));
	if (part.length != part[0]+1)
		throw new Error('File format invalid');
	sGroups[sid][propName] = part.slice(1);
}

chem.Molfile.parsePropertyLines = function (ctab, ctabLines, shift, end)
{
    var mf = chem.Molfile;
    var props = new chem.Map();
    var sGroups = {};
    while (shift < end)
    {
        var line = ctabLines[shift];
        if (line.charAt(0) == 'M')
        {
            var type = line.slice(3, 6);
            var propertyData = line.slice(6);
            if (type == "END") {
                break;
            } else if (type == "CHG") {
                if (!props.get('charge'))
                    props.set('charge', new chem.Map());
                props.get('charge').update(mf.readKeyValuePairs(propertyData));
            } else if (type == "RAD") {
                if (!props.get('radical'))
                    props.set('radical', new chem.Map());
                props.get('radical').update(mf.readKeyValuePairs(propertyData));
            }else if (type == "ISO") {
                if (!props.get('isotope'))
                    props.set('isotope', new chem.Map());
                props.get('isotope').update(mf.readKeyValuePairs(propertyData));
            }else if (type == "RBC") {
                if (!props.get('ringBondCount'))
                    props.set('ringBondCount', new chem.Map());
                props.get('ringBondCount').update(mf.readKeyValuePairs(propertyData));
            } else if (type == "SUB") {
                if (!props.get('substitutionCount'))
                    props.set('substitutionCount', new chem.Map());
                props.get('substitutionCount').update(mf.readKeyValuePairs(propertyData));
            } else if (type == "UNS") {
                if (!props.get('unsaturatedAtom'))
                    props.set('unsaturatedAtom', new chem.Map());
                props.get('unsaturatedAtom').update(mf.readKeyValuePairs(propertyData));
//            else if (type == "LIN") // link atom
//                ;
            } else if (type == "ALS") { // atom list
                if (!props.get('atomList'))
                    props.set('atomList', new chem.Map());
                props.get('atomList').update(
                    mf.parsePropertyLineAtomList(
                    mf.partitionLine(propertyData, [1,3,3,1,1,1]),
                    mf.partitionLineFixed(propertyData.slice(10), 4, false)));
            } else if (type == "STY") { // introduce s-group
				mf.initSGroup(sGroups, propertyData);
            } else if (type == "SST") {
				mf.applySGroupProp(sGroups, 'subtype', propertyData);
            } else if (type == "SLB") {
				mf.applySGroupProp(sGroups, 'label', propertyData, true);
            } else if (type == "SCN") {
				mf.applySGroupProp(sGroups, 'connectivity', propertyData);
            } else if (type == "SAL") {
				mf.applySGroupArrayProp(sGroups, 'atoms', propertyData);
            } else if (type == "SBL") {
				mf.applySGroupArrayProp(sGroups, 'bonds', propertyData);
            } else if (type == "SPA") {
				mf.applySGroupArrayProp(sGroups, 'patoms', propertyData);
            } else if (type == "SMT") {
				var sid = mf.parseDecimalInt(propertyData.slice(0, 4))-1;
				var subscript = propertyData.slice(4);
				if (sGroups[sid].type == "MUL")
					sGroups[sid]['mult'] = mf.parseDecimalInt(subscript);
				else
					sGroups[sid]['subscript'] = subscript;
            }
        }
        ++shift;
    }
	for (var sid in sGroups) {
		console.log(sid);
		console.log(sGroups[sid]);
		mf.processGroup(ctab, sGroups[sid]);
	}
    return props;
}

chem.Molfile.applyAtomProp = function (atoms /* Pool */, values /* chem.Map */, propId /* string */, clean /* boolean */)
{
    values.each(function(aid, propVal){
        atoms.get(aid)[propId] = propVal;
    });
}

chem.Molfile.parseCTabV2000 = function (ctab, ctabLines, countsSplit)
{
    var i;
    var mf = chem.Molfile;
    var atomCount = mf.parseDecimalInt(countsSplit[0]);
    var bondCount = mf.parseDecimalInt(countsSplit[1]);
    var atomListCount = mf.parseDecimalInt(countsSplit[2]);
    ctab.isChiral = mf.parseDecimalInt(countsSplit[4]) != 0;
    var stextLinesCount = mf.parseDecimalInt(countsSplit[5]);
    var propertyLinesCount = mf.parseDecimalInt(countsSplit[10]);

    var shift = 1;
    var atomLines = ctabLines.slice(shift, shift + atomCount);
    shift += atomCount;
    var bondLines = ctabLines.slice(shift, shift + bondCount);
    shift += bondCount;
    var atomListLines = ctabLines.slice(shift, shift + atomListCount);
    shift += atomListCount + stextLinesCount;

    var atoms = atomLines.map(mf.parseAtomLine);
    for (i = 0; i < atoms.length; ++i)
        ctab.atoms.add(atoms[i]);
    var bonds = bondLines.map(mf.parseBondLine);
    for (i = 0; i < bonds.length; ++i)
        ctab.bonds.add(bonds[i]);

    var atomLists = atomListLines.map(mf.parseAtomListLine);
    atomLists.each(function(pair){
       ctab.atoms.get(pair.aid).atomList = pair.atomList;
    });

    var props = mf.parsePropertyLines(ctab, ctabLines, shift,
        Math.min(ctabLines.length, shift + propertyLinesCount));
    props.each(function (propId, values) {
        mf.applyAtomProp(ctab.atoms, values, propId);
    });
	
    return ctab;
}

// split a line by spaces outside parentheses
chem.Molfile.spaceparsplit = function (line)
{
    var split = [], pc = 0, c, i, i0 = -1;
    var line_array = line.toArray(); // IE7 doesn't support line[i]
	var quoted = false;

    for (i = 0; i < line.length; ++i)
    {
        c = line_array[i];
        if (c == '(')
            pc++;
        else if (c == ')')
            pc--;
		if (c == '"')
			quoted = !quoted;
        if (!quoted && line_array[i] == ' ' && pc == 0) {
            if (i > i0 + 1)
                split.push(line.slice(i0+1, i));
            i0 = i;
        }
    }
    if (i > i0 + 1)
        split.push(line.slice(i0 + 1, i));
    i0 = i;
    return split;
}

chem.Molfile.splitonce = function (line, delim)
{
    var p = line.indexOf(delim);
    return [line.slice(0,p),line.slice(p+1)];
}

chem.Molfile.splitSGroupDef = function (line)
{
	var split = [];
	var braceBalance = 0;
	for (var i = 0; i < line.length; ++i) {
		var c = line.charAt(i);
		if (c == '(') {
			braceBalance++;
		} else if (c == ')') {
			braceBalance--;
		} else if (c == ' ' && braceBalance == 0) {
			split.push(line.slice(0, i));
			line = line.slice(i+1).strip();
			i = 0;
		}
	}
	if (braceBalance != 0)
		throw "Brace balance broken. S-group properies invalid!";
	if (line.length > 0)
		split.push(line.strip());
	return split;
}

chem.Molfile.parseBracedNumberList = function (line)
{
	if (!line)
		return null;
	var list = [];
	line = line.strip();
	line = line.substr(1, line.length-2);
	var split = line.split(" ");
	for (var i = 1; i < split.length; ++i) { // skip the first element
		list.push(split[i]-0);
	}
	return list;
}

chem.Molfile.parseCTabV3000 = function (ctab, ctabLines, countsSplit)
{
    var mf = chem.Molfile;
    ctab.isChiral = mf.parseDecimalInt(countsSplit[4]) != 0;

    var shift = 1;
    if (ctabLines[shift++].strip() != "M  V30 BEGIN CTAB")
        throw Error("CTAB V3000 invalid");
    if (ctabLines[shift].slice(0, 13) != "M  V30 COUNTS")
        throw Error("CTAB V3000 invalid");
    var vals = ctabLines[shift].slice(14).split(' ');
    ctab.isChiral = (mf.parseDecimalInt(vals[4]) == 1);
    shift++;

    if (ctabLines[shift++].strip() != "M  V30 BEGIN ATOM")
        throw Error("CTAB V3000 invalid");
    var line;
    while (shift < ctabLines.length) {
        line = mf.stripV30(ctabLines[shift++]).strip();
        if (line.strip() == 'END ATOM')
            break;
        while (line[line.length-1] == '-')
            line = (line + mf.stripV30(ctabLines[shift++])).strip();
        ctab.atoms.add(mf.parseAtomLineV3000(line));
    }
    
    if (ctabLines[shift++].strip() == "M  V30 BEGIN BOND")
    {
        while (shift < ctabLines.length) {
            line = mf.stripV30(ctabLines[shift++]).strip();
            if (line.strip() == 'END BOND')
                break;
            while (line[line.length-1] == '-')
                line = (line + mf.stripV30(ctabLines[shift++])).strip();
            ctab.bonds.add(mf.parseBondLineV3000(line));
        }
    }

	// TODO: let sections follow in arbitrary order
	var sgroups = {};
    while (ctabLines[shift++].strip() == "M  V30 BEGIN SGROUP")
    {
        while (shift < ctabLines.length) {
            line = mf.stripV30(ctabLines[shift++]).strip();
            if (line.strip() == 'END SGROUP')
                break;
            while (line[line.length-1] == '-')
                line = (line.substr(0, line.length - 1) +
					mf.stripV30(ctabLines[shift++])).strip();
			var split = mf.splitSGroupDef(line);
			var sg = {};
			sg.number = split[0] - 0;
			sg.type = split[1];
			sg.label = split[2] - 0;
			sgroups[sg.number] = sg;
			var props = {};
			for (var i = 3; i < split.length; ++i) {
				var subsplit = split[i].split('=');
				if (subsplit.length != 2)
					throw "A record of form AAA=BBB or AAA=(...) expected, got '" + split + "'";
				var name = subsplit[0];
				if (!(name in props))
					props[name] = [];
				props[name].push(subsplit[1]);
			}	
			sg.atoms = mf.parseBracedNumberList(props['ATOMS'][0]);
			sg.patoms = mf.parseBracedNumberList(props['PATOMS'][0]); // TODO: make optional?
			sg.xbonds = mf.parseBracedNumberList(props['XBONDS'][0]);
			var brkxyzStrs = props['BRKXYZ'];
			sg.brkxyz = [];
			for (var j = 0; j < brkxyzStrs.length; ++j)
				sg.brkxyz.push(mf.parseBracedNumberList(brkxyzStrs[j]));
			sg.mult = props['MULT'][0]-0;
			mf.processGroup(ctab, sg);
		}
    }

    return ctab;
}

chem.Molfile.processGroup = function (ctab, data) /* chem.SGroup */
{
	var sg = new chem.SGroup('MUL');
	sg.id = ctab.sgroups.add(sg);
	
	var atomReductionMap = {};
	console.log(data);
	var patoms = data.patoms;
	var patomsMap = {};
	for (var m = 0; m < patoms.length; ++m) {
		patomsMap[patoms[m]-1] = patoms[m]-1;
	}
	console.log(patomsMap);
	for (var k = 1; k < data.mult; ++k) {
		for (m = 0; m < patoms.length; ++m) {
			ctab.atoms.get(data.atoms[k * patoms.length + m]-1).pos.y -= 3*k;
			atomReductionMap[data.atoms[k * patoms.length + m]-1] = patoms[m]-1;
		}
	}
	console.log(atomReductionMap);

	var bondsToRemove = [];
	ctab.bonds.each(function(bid, bond){
		var beginIn = bond.begin in atomReductionMap;
		var endIn = bond.end in atomReductionMap;
		if (beginIn && endIn
			|| beginIn && bond.end in patomsMap
			|| endIn && bond.begin in patomsMap) {
			bondsToRemove.push(bid);
		} else if (beginIn) {
			bond.begin = atomReductionMap[bond.begin];
		} else if (endIn) {
			bond.end = atomReductionMap[bond.end];
		}
	}, this);
	console.log(bondsToRemove);
	for (var b = 0; b < bondsToRemove.length; ++b) {
		ctab.bonds.remove(bondsToRemove[b]);
	}
	for (var a in atomReductionMap) {
		ctab.atoms.remove(a);
	}
	for (var aid in patomsMap) {
		sg.data.atoms.push(aid);
		ctab.atoms.get(aid).sgroup = sg.id;
	}
	sg.data.mul = data.mult;
}

chem.Molfile.parseCTab = function (/* string */ ctabLines) /* chem.Molecule */
{
	ctabLines = ctabLines.slice(3);
    var i = 0;
    var mf = chem.Molfile;
    var ctab = new chem.Molecule();
    var countsSplit = mf.partitionLine(ctabLines[0], mf.fmtInfo.countsLinePartition);
    var version = countsSplit[11].strip();
    if (version == 'V2000')
        return this.parseCTabV2000(ctab, ctabLines, countsSplit);
    else if (version == 'V3000')
        return this.parseCTabV3000(ctab, ctabLines, countsSplit);
    else
        throw Error("Molfile version unknown: " + version);
}

chem.MolfileSaver = function (v3000)
{
    this.molecule = null;
    this.molfile = null;
    
    if (arguments.length > 0)
        this.v3000 = v3000;
    else
        this.v3000 = false;
}

chem.MolfileSaver.prototype.prepareSGroups = function ()
{
	// TODO: clone molecule before changing
	var mol = this.molecule;
	var sgs = this.molecule.sgroups;
	sgs.each(function(id, sg) {
		if (sg.type == 'MUL') {
			for (var j = 0; j < sg.mult - 1; ++j) {
				for (var i = 0; i < sg.data.atoms.length; ++i) {
					var aid = sg.data.atoms[i];
					mol.atoms.

					//console.log(aid);
				}
			}
		}
	});
}

chem.MolfileSaver.prototype.saveMolecule = function (molecule)
{
	console.log(molecule);
    this.molecule = molecule;
    this.molfile = '';

	this.prepareSGroups();
	return;
    
    this.writeHeader();
    
    // TODO: saving to V3000
    this.writeCTab2000(molecule);
        
    return this.molfile;
}

chem.MolfileSaver.prototype.writeHeader = function ()
{
    var date = new Date();
    
    this.writeCR();
    this.writeWhiteSpace(2);
    this.write('Ketcher');
    this.writeWhiteSpace();
    this.writeCR((date.getMonth() + 1).toPaddedString(2) + date.getDate().toPaddedString(2) + (date.getFullYear() % 100).toPaddedString(2) + 
        date.getHours().toPaddedString(2) + date.getMinutes().toPaddedString(2) + '2D 1   1.00000     0.00000     0');
    this.writeCR();
}

chem.MolfileSaver.prototype.write = function (str)
{
    this.molfile += str;
}

chem.MolfileSaver.prototype.writeCR = function (str)
{
    if (arguments.length == 0)
        str = '';
        
    this.molfile += str + '\n';
}

chem.MolfileSaver.prototype.writeWhiteSpace = function (length)
{
    if (arguments.length == 0)
        length = 1;
        
    length.times(function ()
    {
        this.write(' ');
    }, this);
}

chem.MolfileSaver.prototype.writePadded = function (str, width)
{
    this.write(str);
    this.writeWhiteSpace(width - str.length);
}

chem.MolfileSaver.prototype.writePaddedNumber = function (number, width)
{
    var str = number.toString();
    
    this.writeWhiteSpace(width - str.length);
    this.write(str);
}

chem.MolfileSaver.prototype.writePaddedFloat = function (number, width, precision)
{
    var str = number.toFixed(precision).replace(',', '.');
    
    this.writeWhiteSpace(width - str.length);
    this.write(str);
}

chem.MolfileSaver.prototype.writeCTab2000Header = function ()
{
    this.writePaddedNumber(this.molecule.atoms.count(), 3);
    this.writePaddedNumber(this.molecule.bonds.count(), 3);
    
    this.writePaddedNumber(0, 3);
    this.writeWhiteSpace(3);
    this.writePaddedNumber(this.molecule.isChiral ? 1 : 0, 3);
    this.writePaddedNumber(0, 3);
    this.writeWhiteSpace(12);
    this.writePaddedNumber(999, 3);
    this.writeCR(' V2000');
}

chem.MolfileSaver.prototype.writeCTab2000 = function ()
{
    this.writeCTab2000Header();
    
    this.mapping = {};
    var i = 1;

	var atomList_list = [];
    this.molecule.atoms.each(function (id, atom)
    {
        this.writePaddedFloat(atom.pos.x, 10, 4);
        this.writePaddedFloat(atom.pos.y, 10, 4);
        this.writePaddedFloat(0, 10, 4);
        this.writeWhiteSpace();
		
		var label = atom.label;
		if (atom.atomList != null) {
			label = 'L';
			atomList_list.push(id);
		}
        this.writePadded(label, 3);
        this.writePaddedNumber(0, 2);
        this.writePaddedNumber(0, 3);
        this.writePaddedNumber(0, 3);

        // TODO: hydrogen count
        this.writePaddedNumber(0, 3);

        if (Object.isUndefined(atom.stereoCare))
            atom.stereoCare = 0;
        this.writePaddedNumber(atom.stereoCare, 3);
        
        this.writePaddedNumber(atom.valence, 3);
        
        this.writePaddedNumber(0, 3);
        this.writeWhiteSpace(6);

        if (Object.isUndefined(atom.aam))
            atom.aam = 0;
        this.writePaddedNumber(atom.aam, 3);
        
        if (Object.isUndefined(atom.invRet))
            atom.invRet = 0;
        this.writePaddedNumber(atom.invRet, 3);
        
        if (Object.isUndefined(atom.exactChangeFlag))
            atom.exactChangeFlag = 0;
        this.writePaddedNumber(atom.exactChangeFlag, 3);

        this.writeCR();
        
        this.mapping[id] = i;
        i++;
    }, this);
    
    this.molecule.bonds.each(function (id, bond)
    {
        this.writePaddedNumber(this.mapping[bond.begin], 3);
        this.writePaddedNumber(this.mapping[bond.end], 3);
        this.writePaddedNumber(bond.type, 3);

        if (Object.isUndefined(bond.stereo))
            bond.stereo = 0;
        this.writePaddedNumber(bond.stereo, 3);

        this.writeWhiteSpace(3);

        if (Object.isUndefined(bond.topology))
            bond.topology = 0;
        this.writePaddedNumber(bond.topology, 3);

        if (Object.isUndefined(bond.reactingCenterStatus))
            bond.reactingCenterStatus = 0;
        this.writePaddedNumber(bond.reactingCenterStatus, 3);

        this.writeCR();
    }, this);
    
    var charge_list = new Array();
    var isotope_list = new Array();
    
    this.molecule.atoms.each(function (id, atom)
    {
        if (atom.charge != 0)
            charge_list.push(id);
        if (atom.isotope != 0)
            isotope_list.push(id);
    });
    
    if (charge_list.length > 8)
    {
        // TODO: write in several blocks
    } else if (charge_list.length > 0) 
    {
        this.write('M  CHG');
        this.writePaddedNumber(charge_list.length, 3);
        
        charge_list.each(function (id)
        {
            this.writeWhiteSpace();
            this.writePaddedNumber(this.mapping[id], 3);
            this.writeWhiteSpace();
            this.writePaddedNumber(this.molecule.atoms.get(id).charge, 3);
        }, this);

        this.writeCR();
    }
    
    if (isotope_list.length > 8)
    {
        // TODO: write in several blocks
    } else if (isotope_list.length > 0) 
    {
        this.write('M  ISO');
        this.writePaddedNumber(isotope_list.length, 3);
        
        isotope_list.each(function (id)
        {
            this.writeWhiteSpace();
            this.writePaddedNumber(this.mapping[id], 3);
            this.writeWhiteSpace();
            this.writePaddedNumber(this.molecule.atoms.get(id).isotope, 3);
        }, this);

        this.writeCR();
    }

    if (atomList_list.length > 0)
    {
		for (var j = 0; j < atomList_list.length; ++j) {
			var aid = atomList_list[j];
			var atomList = this.molecule.atoms.get(aid).atomList;
			this.write('M  ALS');
			this.writePaddedNumber(aid+1, 4);
			this.writePaddedNumber(atomList.ids.length, 3);
			this.writeWhiteSpace();
			this.write(atomList.notList ? 'T' : 'F');

			var labelList = atomList.labelList();
			for (var k = 0; k < labelList.length; ++k) {
				this.writeWhiteSpace();
				this.writePadded(labelList[k], 3);
			}
			this.writeCR();
		}
    }

    // TODO: write M  RAD
    // TODO: write M  APO
    // TODO: write M  AAL
    // TODO: write M  RGP
    // TODO: write M  LOG

    this.writeCR('M  END');
}

chem.Molfile.parseRxn = function (/* string[] */ ctabLines) /* chem.Molecule */
{
    var mf = chem.Molfile;
	ctabLines = ctabLines.slice(4);
    var countsSplit = mf.partitionLine(ctabLines[0], mf.fmtInfo.rxnItemsPartition);
	var nReactants = countsSplit[0]-0,
		nProducts = countsSplit[1]-0,
		nAgents = countsSplit[2]-0;
	ctabLines = ctabLines.slice(2); // consume counts line and following $MOL

	var ret = new chem.Molecule();
	var molLines = [];
	var i0 = 0, i;
	for (i = 0; i < ctabLines.length; ++i)
		if (ctabLines[i].substr(0, 4) == "$MOL") {
			molLines.push(ctabLines.slice(i0, i));
			i0 = i + 1;
		}
	molLines.push(ctabLines.slice(i0));
	for (var j = 0; j < molLines.length; ++j) {
		var mol = chem.Molfile.parseCTab(molLines[j]);
		var fragmentType = (j < nReactants ? chem.Molecule.FRAGMENT.REACTANT :
			(j < nReactants + nProducts ? chem.Molecule.FRAGMENT.PRODUCT :
			chem.Molecule.FRAGMENT.AGENT));
		var fragmentId = chem.Molecule.fragments.add(fragmentType);
		mol.atoms.each(function(aid, atom){
			atom.fragment = fragmentId;
		}, this);
		ret.merge(mol);
	}
	return ret;
}