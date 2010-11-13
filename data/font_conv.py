import sys
from sys import stdout

def ConvertFont(fn_in, fn_out):
    fin = open(fn_in, "read")
    fout = open(fn_out, "write")
    letters = []
    
    line = fin.readline()
    n = int(line)
    fout.write("_count = %d;\n" % n)
    for line in fin:
        words = line.split()
        
        if words[0] == '+':
            words[0] = 'plus'
        elif words[0] == '-':
            words[0] = 'minus'

        letters.append(words[0])
        fout.write("double descr_%s[%d] = {%s" % (words[0], n * 2, words[1]))
        for s in words[2:]:
            fout.write(", %s" % s)
        fout.write("};\n")

    for s in letters:
        fout.write("FONT_INIT(%s);\n" % s)

if __name__ == '__main__':
    ConvertFont(sys.argv[1], sys.argv[1] + ".inc")

