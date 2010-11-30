import sys
from sys import stdout

def ConvertFont(fn_in, fn_out):
    fin = open(fn_in, "read")
    fout = open(fn_out, "write")
    letters = []
    
    line = fin.readline()
    line = line.split()
    n = int(line[0])
    fonts = int(line[1])
    letters = int(line[2])
    fout.write("""_count = %d;
int fonts_count = %d, letters_count = %d, i;
SymbolClass *cls;
SymbolFeatures *sf;
_classes.resize(letters_count);
""" % (n, fonts, letters))

    for i in range(letters):
        curChar = fin.readline()[0]

        fout.write("""i = %d;
cls = &_classes[i];
cls->sym = '%s';
_mapping[cls->sym] = i;
cls->shapes.resize(fonts_count);
""" % (i, curChar))
        
        for j in range(fonts):
            inner_contours = int(fin.readline())
            descriptors = fin.readline().split()
            inner_descriptors = []
            for _ in range(inner_contours):
                inner_descriptors.append(fin.readline().split())
            
            fout.write("""sf = &cls->shapes[%d];
sf->inner_contours_count = %d;
sf->descriptors.resize(2 * _count);
""" % (j, inner_contours))
            for k in range(2 * n):
                fout.write("""sf->descriptors[%d] = %s; """ % (k, descriptors[k]))

            fout.write("\nsf->inner_descriptors.resize(sf->inner_contours_count);\n")
            for k in range(inner_contours):
                fout.write("sf->inner_descriptors[%d].resize(2 * _count);\n" % k);
                for l in range(2 * n):
                    fout.write("""sf->inner_descriptors[%d][%d] = %s; """ % (k, l, inner_descriptors[k][l]))                    

if __name__ == '__main__':
    ConvertFont(sys.argv[1], sys.argv[1] + ".inc")

