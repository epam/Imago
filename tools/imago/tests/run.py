import os
import subprocess
import sys
from time import time
from xml.etree.ElementTree import Element, tostring

dirname = os.path.dirname(os.path.abspath(__file__))
imago_root = os.path.normpath(
    os.path.join(os.path.abspath(__file__), "..", "..", "..", "..")
)
sys.path.append((os.path.join(imago_root, "third_party/indigo/api/python")))
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
    testCase = Element("test-case", name=name, time=str(round(time, 2)))
    if error:
        failure = Element("failure")
        message = Element("message")
        message.text = error
        failure.append(message)
        testCase.append(failure)
    return testCase


def testImagoConsole(mol, image):
    global totalImages, successfullyRecognizedImages, indigoFailedImages, results
    if os.name == "nt":
        execSuffix = ".exe"
    else:
        execSuffix = ""
    beginTime = time()

    resultmolpath = image.replace(".png", ".out.mol")

    subprocess.check_call(
        [f"{imago_root}/dist/imago{execSuffix}", image, "-o", resultmolpath]
    )
    totalTime = time() - beginTime
    error = None
    try:
        stdMol = indigo.loadMoleculeFromFile(mol)
        resultMol = indigo.loadMoleculeFromFile(resultmolpath)
        if indigo.exactMatch(stdMol, resultMol):
            successfullyRecognizedImages += 1
        else:
            error = "Imago"
        totalImages += 1
    except IndigoException as e:
        sys.stderr.write("Indigo: " + e.value + "\n")
        indigoFailedImages += 1
        error = "Indigo: " + e.value
    finally:
        results.append(
            createTestCase(image.split(os.path.sep)[-1], totalTime, error)
        )


if __name__ == "__main__":
    indigo = Indigo()
    indigo.setOption("ignore-noncritical-query-features", True)

    successfullyRecognizedImages = 0
    totalImages = 0
    indigoFailedImages = 0

    xmlReport = Element("test-results")
    testSuite = Element("test-suite", name="Imago")
    results = Element("results")

    for root, dirs, files in os.walk(os.path.join(dirname, "images")):
        for f in sorted(files):
            file = os.path.join(root, f)
            if file.endswith(".mol"):
                if os.path.exists(file.replace(".mol", ".png")):
                    testImagoConsole(file, file.replace(".mol", ".png"))
                if os.path.exists(file.replace(".mol", ".jpg")):
                    testImagoConsole(file, file.replace(".mol", ".jpg"))

    testSuite.append(results)
    xmlReport.append(testSuite)
    with open("report.xml", "wb") as f:
        indent(xmlReport)
        f.write(tostring(xmlReport))

    print("Test results:")
    print("Total images: %s" % totalImages)
    print(
        "Successfully recognized images: %s, rate: %s "
        % (
            successfullyRecognizedImages,
            float(successfullyRecognizedImages) / float(totalImages),
        )
    )
    print("Indigo fails: %s" % indigoFailedImages)

    exit_code = 0 if successfullyRecognizedImages == totalImages else 1
    exit(exit_code)
