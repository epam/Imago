# Imago OCR

## Overview

Imago OCR is a toolkit for 2D chemical structure image recognition. It
contains a [command-line utility](https://lifescience.opensource.epam.com/imago/imago_console.html),
as well as a [documented C](https://lifescience.opensource.epam.com/imago/c.html), 
Python and Java API for developers. Imago is completely free and
open-source, while also available on a commercial basis.

The core part of Imago is written from scratch in modern C++. It uses
the best known algorithms for optical recognition. That guarantees
Imago's outstanding portability and performance.

### Recognizable Molecule Features

-  Single, double, triple bonds, bridged bonds
-  Atom labels, subscripts, isotopes, charges
-  Superatoms and abbreviations expansion
-  Aromatic rings
-  Stereochemistry (up- and down-bonds)

## Comparison with other systems

We created a detailed report with sets of different images that compares
Imago OCR with other publicly available solutions. The report is
available on a [separate page](https://lifescience.opensource.epam.com/imago/imago-report.html).
The scripts and the image sets are available in the [download
section](https://lifescience.opensource.epam.com/download/imago.html).

If you can suggest other test sets or other publicly available solutions
we would be happy to include them too in the report.

## Portability

Imago library is written in portable C++ and supports Linux, Windows,
and Mac OS X operating systems, both 32-bit and 64-bit versions of each
system.

## Dependencies

The dependencies are included into the distribution packages, and so you
do not need to download any of them separately to run the programs or to
compile the source code.

Imago C++ dependencies:

- [OpenCV](https://opencv.org).
- [Indigo](https://github.com/epam/Indigo).


## Supported Data Formats

Both the Imago OCR project and the ``imago_console`` tool are supporting
the most popular raster image formats: ``PNG``, ``JPEG``, ``BMP (using RGB 24bpp)``,
``DIB (using RGB 24bpp)``, ``TIFF``, ``PBM`` and others (depending on platform).
Imago OCR Visual Tool users can also open ``PDF`` files, choose the
needed document page (if it is ``PDF`` or ``TIFF``), and select a
fragment that should be recognized.

Developers who use the C API can pass supported format images or raw
image data to the library. Recognition result can be saved as ``MDL``
(Symyx, Accelrys) Molfiles. Imago OCR Visual Tool also provides a
possibility to copy the recognized molecule to the system clipboard.

## Download and Install

Look at the [Downloads](https://lifescience.opensource.epam.com/download/imago.html) page for the
installation package suitable for your system. There is an installer for
Windows, and zipfiles for Linux and Mac OS X, which you can just unpack
into ``/usr/local/bin`` or ``/opt`` directory, or into your home
directory.

You can run Imago OCR Visual Tool even without installing any files
using Java Web Start technology. Open the [following
JNLP file](https://lifescience.opensource.epam.com/content/downloads/imago-2.0.0/imago-ocr-visual-tool.jnlp>)
to execute Imago OCR Visual Tool.

## Feedback

Do you need assistance using our tools? Do you need a feature? Do you
want to send a patch to us? Did you find a bug? Please write to the following e-mail and let us know:

[lifescience.opensource@epam.com](mailto:lifescience.opensource@epam.com).

## Commercial Availability

If the Apache-licensed Imago does not fit your needs, please contact us to discuss the purchase of a commercial license.
You may need the commercial license if you want to:

-  Receive ongoing support and maintenance
-  Do any other development/testing required for a proprietary software product

Visit our [SolutionsHub page](https://solutionshub.epam.com/solution/imago) for more details.
