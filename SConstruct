import os as OS, platform
from os.path import normpath, join, basename, abspath

bits = ''
machine = platform.machine()
if machine in ('i386', 'x86', 'i686'):
   bits = 'x86'
else:
   bits = 'x64'   

AddOption('--target',
          dest='target',
          type='string',
          action='store',
          default=bits,
          nargs=1,
          help='cross-compiling option: x86 or x64')

AddOption('--DEBUG',
          dest='debug',
          action='store_true',
          default=False,
          help='Debug/Release')

target_bits = GetOption('target')
if not target_bits in ('x86', 'x64'):
   print "Target_bits parameter is incorrect"
   Exit(0)

debug = GetOption('debug')

env = Environment(ENV=OS.environ)

print COMMAND_LINE_TARGETS
print bits
print target_bits
print env['PLATFORM']

os = ''
if env['PLATFORM'] == 'win32':
   os = 'Win'
   target_arch = ''
   if bits == 'x64':
      if target_bits == 'x86':
         libs = ['libpng32.lib']
         target_arch = 'x86'
      else:
         libs = ['libpng64.lib']
         target_arch = 'amd64'
   elif bits == 'x86':
      if target_bits == 'x64':
         libs = ['libpng64.lib']
         target_arch = 'amd64'
      else:
         libs = ['libpng32.lib']
         target_arch = 'x86'

   env = Environment(ENV=OS.environ,
              CCFLAGS = '/O2 /Oi /GL- /GR- /EHsc /D "_CRT_SECURE_NO_DEPRECATE" /MT /D "IMAGO_FONT_BUILT_IN" /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_UNICODE" /Gy /W3 /nologo /c /wd4345 /wd4244',
              CPPPATH = ['#libpng'],
              LIBPATH = ['#libpng'],
              LIBS = libs,
              LINKFLAGS = '/nologo',
              TARGET_ARCH = target_arch
              )
   #TODO:
   if debug:
      pass
   else:
      pass
      
elif env['PLATFORM'] == 'posix':
   os = 'Linux'
   common_ccflags = '-Wall -fomit-frame-pointer -D IMAGO_FONT_BUILT_IN'
   special_ccflags = ''
   special_linkflags = ''
   if bits == 'x64':
      special_ccflags = special_linkflags = ' -m64'
      if target_bits == 'x86':
         special_ccflags = special_linkflags = ' -m32'
   elif bits == 'x86':
      special_ccflags = special_linkflags = ' -m32'
      if target_bits == 'x64':
         special_ccflags = special_linkflags = ' -m64'
      
   if debug:
      common_ccflags += ' -g'
   else:
      common_ccflags += ' -O2'

   env.Append(CCFLAGS = common_ccflags + special_ccflags,
              LIBS = ['m', 'png', 'pthread'],
              LINKFLAGS = special_linkflags
              )

elif env['PLATFORM'] == 'darwin':
   AddOption('--macosx',
             dest='macosx',
             type='string',
             action='store',
             default='10.5',
             nargs=1,
             help='version of macosx: 10.5 or 10.6')
   os = 'Mac'
   target_bits = 'universal'
   macosx_version = GetOption('macosx')

   if not macosx_version in ('10.5, 10.6'):
      print 'Unsupported MacOSX version'
      Exit(0)

   macosx_ccflags = ' -isysroot /Developer/SDKs/MacOSX{0}.sdk -mmacosx-version-min={0}'.format(macosx_version)
   common_ccflags = '-D IMAGO_FONT_BUILT_IN -Wall -fomit-frame-pointer' + macosx_ccflags

   if debug:
      common_ccflags += ' -g'
   else:
      common_ccflags += ' -O2'

   arch_flags = ' -arch ppc -arch i386 -arch x86_64'
   env.Append(CCFLAGS = common_ccflags + arch_flags,
              LINKFLAGS = arch_flags,
              LIBS = ['m', 'png', 'pthread'],
              CPPPATH = ['/opt/local/include'],
              LIBPATH = ['/opt/local/lib']
             )

#For Boost headers
env.Append(CPPPATH = ['#.'])

env['OS'] = os
if os == 'Mac':
   env['MACOSX_VERSION'] = macosx_version
env['TARGET_BITS'] = target_bits
if os == 'Mac':
   env['BUILDDIR'] = 'build_' + target_bits + '_' + macosx_version
else:
   env['BUILDDIR'] = 'build_' + target_bits

output = abspath('output')
if debug:
   env['BUILDDIR'] += '_debug/'
   env['OUTPUT_DIR'] = join(output, 'debug')
else:
   env['BUILDDIR'] += '_release/'
   env['OUTPUT_DIR'] = join(output, 'release')

target_suffix = target_bits
if env['PLATFORM'] == 'darwin':
   target_suffix += '_' + macosx_version
env['TARGET_SUFFIX'] = target_suffix

Export('env')

SConscript('imago/SConscript')
SConscript('imago_c/SConscript')
SConscript('alter-ego/SConscript')

if COMMAND_LINE_TARGETS == ['all']:
   SConscript('jimago/SConscript')   
   SConscript('iSMILES/SConscript')
   SConscript('ego/SConscript')
else:
   if 'jimago' in COMMAND_LINE_TARGETS:
      SConscript('jimago/SConscript')
   elif 'ego' in COMMAND_LINE_TARGETS:
      if not 'jimago' in COMMAND_LINE_TARGETS:
         SConscript('jimago/SConscript')
      if not 'ismiles_c' in COMMAND_LINE_TARGETS:
         SConscript('iSMILES/SConscript')
      SConscript('ego/SConscript')
   elif 'tests' in COMMAND_LINE_TARGETS:
      SConscript('tests/vs/imagotest/SConscript')
   elif 'ismiles_c' in COMMAND_LINE_TARGETS:
      SConscript('iSMILES/SConscript')
