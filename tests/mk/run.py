import sys
import os                 
sys.path.append(os.path.abspath(os.path.join(os.curdir, 'indigo')))
from indigo import Indigo, IndigoException        

successfullyRecognizedImages = 0
totalImages = 0
indigoFailedImages = 0

indigo = Indigo()

def testAlterEgo(mol, image):
    global totalImages, successfullyRecognizedImages, indigoFailedImages
    resultMolFile = image.replace(image.split('.')[-1], 'out.mol')
    if os.name == 'nt':
        execSuffix = '.exe'
    else:
        execSuffix = ''
    #print 'alter_ego%s "%s" -o "%s"' % (execSuffix, image, resultMolFile)
    os.system('alter_ego%s "%s" -o "%s"' % (execSuffix, image, resultMolFile))   
    try:
        stdMol = indigo.loadMoleculeFromFile(mol)
        resultMol = indigo.loadMoleculeFromFile(resultMolFile)
        if indigo.exactMatch(stdMol, resultMol):
            successfullyRecognizedImages += 1
        totalImages += 1  	
    except IndigoException, e:
        sys.stderr.write(e + '\n')
        indigoFailedImages += 1
        
for root, dirs, files in os.walk('images'):
    for f in files:
        file = os.path.join(root, f)
        if file.endswith('.mol'):
            if os.path.exists(file.replace('.mol', '.png')):
                testAlterEgo(file, file.replace('.mol', '.png'))
            if os.path.exists(file.replace('.mol', '.jpg')):
                testAlterEgo(file, file.replace('.mol', '.jpg'))

print 'Test results:'
print 'Total images: %s' % totalImages
print 'Successfully recognized images: %s, rate: %s ' % (successfullyRecognizedImages, float(successfullyRecognizedImages) / float (totalImages))
print 'Indigo fails: %s' % indigoFailedImages