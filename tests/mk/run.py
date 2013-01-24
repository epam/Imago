import sys
import os
from xml.etree.ElementTree import Element, tostring
from time import time

sys.path.append(os.path.abspath(os.path.join(os.curdir, 'indigo')))
from indigo import Indigo, IndigoException


def indent(elem, level=0):
    i = "\n" + level * "  "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "  "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            indent(elem, level + 1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i


def createTestCase(name, time, error):
    testCase = Element('test-case', name=name, time=str(round(time, 2)))
    if error:
        failure = Element('failure')
        message = Element('message')
        message.text = error
        failure.append(message)
        testCase.append(failure)
    return testCase


def testImagoConsole(mol, image):
    global totalImages, successfullyRecognizedImages, indigoFailedImages, results
    if os.name == 'nt':
        execSuffix = '.exe'
    else:
        execSuffix = ''
    beginTime = time()
    os.system(os.path.join('..', '..', 'imago_console', 'imago_console%s "%s"' % (execSuffix, image)))
    totalTime = time() - beginTime
    error = None
    try:
        stdMol = indigo.loadMoleculeFromFile(mol)
        resultMol = indigo.loadMoleculeFromFile('molecule.mol')
        if indigo.exactMatch(stdMol, resultMol):
            successfullyRecognizedImages += 1
        else:
            error = 'Imago'
        totalImages += 1
    except IndigoException, e:
        sys.stderr.write('Indigo: ' + e.value + '\n')
        indigoFailedImages += 1
        error = 'Indigo: ' + e.value
    finally:
        results.append(createTestCase(image.split(os.path.sep)[-1], totalTime, error))

if __name__ == '__main__':
    indigo = Indigo()

    successfullyRecognizedImages = 0
    totalImages = 0
    indigoFailedImages = 0

    xmlReport = Element('test-results')
    testSuite = Element('test-suite', name='Imago')
    results = Element('results')

    for root, dirs, files in os.walk('images'):
        for f in sorted(files):
            file = os.path.join(root, f)
            if file.endswith('.mol'):
                if os.path.exists(file.replace('.mol', '.png')):
                    testImagoConsole(file, file.replace('.mol', '.png'))
                if os.path.exists(file.replace('.mol', '.jpg')):
                    testImagoConsole(file, file.replace('.mol', '.jpg'))

    testSuite.append(results)
    xmlReport.append(testSuite)
    with open('report.xml', 'wt') as f:
        indent(xmlReport)
        f.write(tostring(xmlReport))

    print 'Test results:'
    print 'Total images: %s' % totalImages
    print 'Successfully recognized images: %s, rate: %s ' % (successfullyRecognizedImages, float(successfullyRecognizedImages) / float(totalImages))
    print 'Indigo fails: %s' % indigoFailedImages
