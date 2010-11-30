import sys
import Image, ImageFont, ImageDraw

if len(sys.argv) != 3:
    print "Run script as", sys.argv[0], "<input.ttf> <output.png>"
    sys.exit(0);

image = Image.new("RGB", (150, 9000))

draw = ImageDraw.Draw(image)

fontsize = 75
font = ImageFont.truetype(sys.argv[1], fontsize)

draw.rectangle([(0, 0), image.size], fill = (255, 255, 255))

space = fontsize + 50
text = ""
c = "A"
y = 10
for _ in range(0, 26):
    draw.text((30, y), c, font = font, fill = (0, 0, 0))
    c = chr(ord(c) + 1)
    y += space

c = 'a'
for _ in range(0, 26):
    draw.text((30, y), c, font = font, fill = (0, 0, 0))
    c = chr(ord(c) + 1)
    y += space

for c in range(0, 10):
    draw.text((30, y), str(c), font = font, fill = (0, 0, 0))
    y += space


image.save(sys.argv[2])

