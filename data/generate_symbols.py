import sys, os
import Image, ImageFont, ImageDraw

if len(sys.argv) != 3:
    print "Run script as", sys.argv[0], "<input.ttf> <output folder>"
    sys.exit(0);

fontname = sys.argv[1]
fontnamenoext = os.path.basename(sys.argv[1])[:-4]
outdir = sys.argv[2]

assert(len(fontnamenoext) > 0)

symbols = []
symbols += [chr(ord('A') + i) for i in xrange(0, 26)]
symbols += [chr(ord('a') + i) for i in xrange(0, 26)]
symbols += [str(i) for i in xrange(0, 10)]

if not os.path.isdir(outdir):
    os.mkdir(outdir)

print symbols

fontsize = 75
font = ImageFont.truetype(fontname, fontsize)

for s in symbols:
    image = Image.new("RGB", (150, 200))
    draw = ImageDraw.Draw(image)
    
    draw.rectangle([(0, 0), image.size], fill = (255, 255, 255))
    
    draw.text((30, 10), str(s), font = font, fill = (0, 0, 0))
    
    symdir = os.path.join(outdir, s)
    if not os.path.isdir(symdir):
        os.mkdir(symdir)
    sympath = os.path.join(symdir, fontnamenoext + ".png")
    image.save(sympath)

