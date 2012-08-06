import sys
import os                 
sys.path.append(os.path.abspath(os.path.join(os.curdir, 'indigo')))
from indigo import Indigo, IndigoException        
from xml.dom.minidom import Document
from time import time

successfullyRecognizedImages = 0
totalImages = 0
indigoFailedImages = 0
doc = Document()
xml_test_results = doc.createElement("test-results")
doc.appendChild(xml_test_results)
test_suite = doc.createElement("test-suite")
test_suite.setAttribute("name", 'Imago')
results = doc.createElement("results")
indigo = Indigo()

def createTestCase(doc, name, time, error):
   test_case = doc.createElement("test-case")
   test_case.setAttribute("name", name)
   test_case.setAttribute("time", time)
   if error:
      failure = doc.createElement("failure")
      message = doc.createElement("message")
      message_text = doc.createTextNode(error)
      message.appendChild(message_text)
      failure.appendChild(message)
      test_case.appendChild(failure)
   return test_case

def testAlterEgo(mol, image):
    global totalImages, successfullyRecognizedImages, indigoFailedImages, results
    resultMolFile = image.replace(image.split('.')[-1], 'out.mol')
    if os.name == 'nt':
        execSuffix = '.exe'
    else:
        execSuffix = ''
    #print 'alter_ego%s "%s" -o "%s"' % (execSuffix, image, resultMolFile)
    beginTime = time()
    os.system('alter_ego%s "%s" -o "%s"' % (execSuffix, image, resultMolFile))   
    totalTime = time() - beginTime
    error = None
    try:
        stdMol = indigo.loadMoleculeFromFile(mol)
        resultMol = indigo.loadMoleculeFromFile(resultMolFile)
        if indigo.exactMatch(stdMol, resultMol):
            successfullyRecognizedImages += 1
        else:
            error = "Imago"
        totalImages += 1  	
    except IndigoException, e:
        sys.stderr.write(e.message + '\n')
        indigoFailedImages += 1
        error = 'Indigo'
    finally:
        results.appendChild(createTestCase(doc, image, time, error))
   
for root, dirs, files in os.walk(os.path.join('images', '1. Main Set')):
    for f in files:
        file = os.path.join(root, f)
        if file.endswith('.mol'):
            if os.path.exists(file.replace('.mol', '.png')):
                testAlterEgo(file, file.replace('.mol', '.png'))
            if os.path.exists(file.replace('.mol', '.jpg')):
                testAlterEgo(file, file.replace('.mol', '.jpg'))

test_suite.appendChild(results)
xml_test_results.appendChild(test_suite)
doc.appendChild(xml_test_results)
#print doc
#open('report.xml', "w").write(doc.to)   

print 'Test results:'
print 'Total images: %s' % totalImages
print 'Successfully recognized images: %s, rate: %s ' % (successfullyRecognizedImages, float(successfullyRecognizedImages) / float (totalImages))
print 'Indigo fails: %s' % indigoFailedImages