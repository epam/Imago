import sys, os, subprocess

if len(sys.argv) != 3:
    print "Run script as", sys.argv[0], "<input folder> <output.font>"
    sys.exit(0);

indir = sys.argv[1]
outpath = sys.argv[2]

count = 25

assert(os.path.isdir(indir))

symbols = []
symbols += [chr(ord('A') + i) for i in xrange(0, 26)]
symbols += [chr(ord('a') + i) for i in xrange(0, 26)]
symbols += [str(i) for i in xrange(0, 10)]

f = open(outpath, 'w')

f.write("" + str(count) + " " + str(len(symbols)) + "\n")
for sym in symbols:
    if sym >= 'A' and sym <= 'Z':
        symdir = os.path.join(indir, 'capital', sym)
    else:
        symdir = os.path.join(indir, sym)
    glyphs = filter(lambda g: g[-4:] == ".png", os.listdir(symdir))  
    f.write("" + str(sym) + " " + str(len(glyphs)) + "\n")
    for g in glyphs:
        p = subprocess.Popen(["./fd_calc", os.path.join(symdir, g), str(count)], stdout=subprocess.PIPE)
        p.wait()
        assert(p.returncode == 0)
        f.write(p.communicate()[0])

f.close()
    
    
