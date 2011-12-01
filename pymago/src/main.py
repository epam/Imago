import sys
import Image
import scipy as sp, numpy as np
from scipy import ndimage as ndi


def load_image():
    if len(sys.argv) == 1:
        filename = '../iPad2/TS_3_iPad_2_3.JPG'
    elif len(sys.argv) == 2:
        filename = sys.argv[1]

    i = Image.open(filename).convert('L')
    return sp.asarray(i)

def filter_image(img):
    struct = ndi.iterate_structure(ndi.generate_binary_structure(2, 1), 1)
    #tophat
    i = ndi.black_tophat(img, (30, 30)) #structure = struct)
    i = 255 - i
    #gauss
    i = ndi.gaussian_filter(i, (0.5, 0.5))
    #medianBlur
    i = ndi.median_filter(i, 2)
    #otsu threshold
    i = i > 225
    
    return i

def main():
    img = load_image()

    img_filtered = filter_image(img)
    sp.misc.imshow(img_filtered)

if __name__ == '__main__':
    main()
