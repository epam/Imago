import platform, os.path as op, os, subprocess
from optparse import OptionParser

cano = ""
dingo = ""
alterego = ""

def setup_program_paths():
   global cano, dingo, alterego
   bits, _ = platform.architecture()
   if bits == "32bit":
      bits = "x86"
   elif bits == "64bit":
      bits = "x64"

   assert(bits in ("x86", "x64"))

   cano = op.join("indigo-cano", bits, "indigo-cano")
   dingo = op.join("indigo-depict", bits, "indigo-depict")
   alterego = op.join("..", "..", "output", "release", "alter-ego", bits, "alter_ego")
#   print dingo
#   print cano

def parse_command_line():
   parser = OptionParser(usage = "usage: %prog [options]")
   parser.add_option("-o", "--output", dest = "output", default = "def_output", help = "output directory")
   parser.add_option("-f", "--molfiles", dest = "molfiles", help = "path to molfiles")
   parser.add_option("-i", "--images", dest = "images", help = "path to images")
   parser.add_option("-m", "--mode", dest = "mode", help = "program mode: DRC, RC, DR or R")
#   parser.add_option("-q", "--quiet", dest="verbose",  help="don't print status messages to stdout")
   
   (options, args) = parser.parse_args()
   if len(args) != 0:
      print "Wrong command line!"
      parser.print_help()
      return
   elif options.mode is None or options.mode not in ("DRC", "RC", "DR", "R"):
      print "Select correct program mode"
      parser.print_help()
      return
   elif options.output is None or False:
      print "Output dir is not set"
      parser.print_help()
      return
   elif options.mode.find("D") != -1:
      if options.molfiles is None:
         print "Specify directory with molfiles"
         parser.print_help()
         return
      if not options.images is None:
         print "Ignoring parameter --images"
         options.images = None
   elif options.mode.find("R") != -1:
      if options.images is None:
         print "Specify directory with images"
         parser.print_help()
         return
     # if not options.molfiles is None:
      #   print "Ignoring parameter --molfiles"
       #  options.molfiles = None
   elif options.mode.find("C") != -1:
      if options.molfiles is None:
         print "Specify directory with molfiles to compare"
         parser.print_help()
         return

   return options.images, options.molfiles, options.output, options.mode

def popen_dingo(molfile, pngfile):
   dpipe = subprocess.Popen([dingo] + (molfile + " " + pngfile + " -query").split(), 
                            stdin = subprocess.PIPE, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
   
   ret = dpipe.wait()
   if ret != 0:
      print "Dingo oops at", molfile, "with", ret
      for l in dpipe.stderr.readlines():
         print l
      return False
   return True

def popen_imago(pngfile, molfile):
   apipe = subprocess.Popen([alterego] + (pngfile + " -n -o " + molfile).split(), stdin = subprocess.PIPE,
                            stdout = subprocess.PIPE, stderr = subprocess.PIPE)

   ret = apipe.wait()
   if ret != 0:
      print "Imago oops at", molfile, "with", ret
      for l in apipe.stderr.readlines():
         print l
      return False
   return True

def popen_cano(molfile):
   cpipe = subprocess.Popen([cano] + (molfile).split(), stdin = subprocess.PIPE,
                            stdout = subprocess.PIPE, stderr = subprocess.PIPE)

   ret = cpipe.wait()
   if ret != 0:
      print "Cano oops at", molfile, "with", ret
      for l in cpipe.stderr.readlines():
         print l
      return False

   smiles = cpipe.stdout.readline()
   return smiles

def cano_compare(molfile1, molfile2):
   smiles1 = popen_cano(molfile1)
   smiles2 = popen_cano(molfile2)

   if smiles1 is False or smiles2 is False:
      print "Cannot calc SMILES for molecules"
      return False

   if smiles1 == smiles2:
      print "Oh, yeah!"
      return True
   else:
      print "SMILES strings don't match"
      return False

def run_file(infile):
   infile_name = op.basename(infile)
   print "Processing", infile

   if mode.find("D") != -1:
      if infile_name[-3:].lower() != "mol":
         return -1
      pngfile = op.join(output, molfile_name[:-3] + "png")
      if not popen_dingo(infile, pngfile):
         return -1
   else:
      pngfile = infile

   if pngfile[-3:].lower() != "png":
      return -1
  
   imagofile = op.join(output, molfile_name[:-4] + "_imago.mol")
   if not popen_imago(pngfile, imagofile):
      return 0
   
   imagopng =  op.join(output, molfile_name[:-4] + "_imago.png")
   if not popen_dingo(imagofile, imagopng):
      print "Cannot render imago's result"

   if mode.find("C") != -1:
      if cano_compare(infile, imagofile):
         return 1
      else:
         return 0
   
def run_dir():
   files = os.listdir(input)
   total = 0
   success = 0
   for f in files:
      res = run_file(op.join(input, f))
      if res >= 0:
         total += 1
         if res == 1:
            success += 1
   
   print "Success ratio =", success * 1.0 / total

def draw_molecules(molfiles, output):
   molfiles_list = []
   if op.isdir(molfiles):
      molfiles_list = [op.join(molfiles, f) for f in os.listdir(molfiles)]
   elif op.isfile(molfiles):
      molfiles_list = [molfiles]
   else:
      print "Molfiles parameter is incorrect!"
      return None

   drew = []
   for f in molfiles_list:
      if f[-3:].lower() != "mol":
         continue

      f_base = op.basename(f)
      pngfile = op.join(output, f_base[:-3] + "png")
      print "Drawing", f_base
      if popen_dingo(f, pngfile):
         drew.append(pngfile)

   return drew

def recognize_images(drew, output):
   recognized = []
   for img in drew:
      if img[-3:].lower() != "png":
         continue
      
      img_base = op.basename(img)

      imago_mol = op.join(output, img_base[:-4] + "_imago.mol")
      print "Recognizing", img_base
      if popen_imago(img, imago_mol):
         recognized.append(imago_mol)
   
      imagopng =  op.join(output, img_base[:-4] + "_imago.png")
      if not popen_dingo(imago_mol, imagopng):
         print "Cannot render imago's result"

   return recognized

def compare_molecules(recognized, molfiles):
   total = 0
   success = 0
   for f in recognized:
      f_base = op.basename(f)
      f_orig = f_base[:-10] + ".mol"

      second = None

      if op.exists(op.join(molfiles, f_orig)):
         second = op.join(molfiles, f_orig)
      else:
         print "Corresponding molfile for", f, "not found"
         continue

      total += 1
      print "Comparing", f, "and", second
      if cano_compare(f, second):
         success += 1 

      if total == 0:
         ratio = -1
      else:
         ratio = success * 1.0 / total

   return ratio

def run(images, molfiles, output, mode):
   if not op.exists(output):
      os.makedirs(output)

   if mode.find("D") != -1:
      drew = draw_molecules(molfiles, output)
   else:
      if op.isdir(images):
         drew = [op.join(images, f) for f in os.listdir(images)]
      else:
         drew = images
  
   recognized = None
   if mode.find("R") != -1:
      if drew is None or len(drew) == 0:
         print "No images to recognize. Aborting."
         return

      drew.sort()

      recognized = recognize_images(drew, output)


   if mode.find("C") != -1:
      if recognized is None or len(recognized) == 0:
         print "Nothing to compare."
         return

      print molfiles
      ratio = compare_molecules(recognized, molfiles)

      print "Success ratio =", ratio 

def main():
   setup_program_paths()
   
   args = parse_command_line()
   if args is None:
      return

#   print args[0]
#   print args[1]
#   print args[2]
#   print args[3]

   run(args[0], args[1], args[2], args[3])

if __name__ == '__main__':
   main()
