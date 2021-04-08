import distutils.dir_util
import glob
import os
import shutil
import sys

from setuptools import setup

CLASSIFIERS = """\
Development Status :: 4 - Beta
Intended Audience :: Science/Research
Intended Audience :: Developers
License :: OSI Approved :: Apache Software License
Programming Language :: C
Programming Language :: C++
Programming Language :: Python
Programming Language :: Python :: 3
Programming Language :: Python :: 3.5
Programming Language :: Python :: 3.6
Programming Language :: Python :: 3.7
Programming Language :: Python :: 3.8
Programming Language :: Python :: 3.9
Programming Language :: Python :: Implementation :: CPython
Topic :: Software Development
Topic :: Scientific/Engineering :: Chemistry
Operating System :: Microsoft :: Windows
Operating System :: POSIX :: Linux
Operating System :: MacOS
"""

LONG_DESCRIPTION = "Imago is an optical recognition tool for chemical structures"

IMAGO_LIBS = None
PLATFORM_NAME = None

this_dir = os.path.dirname(os.path.abspath(__file__))
repo_root_dir = os.path.dirname(os.path.dirname(this_dir))
repo_dist_lib_dir = os.path.join(repo_root_dir, "dist", "lib")
imago_python_directory = os.path.join(this_dir, "imago")
imago_native_libs_directory = os.path.join(imago_python_directory, "lib")
if not os.path.exists(imago_native_libs_directory):
    print("No native libs found in {}, looking for them in {}".format(imago_native_libs_directory, repo_dist_lib_dir))
    if os.path.exists(repo_dist_lib_dir):
        print("Copying native libs from {}".format(repo_dist_lib_dir))
        shutil.copytree(repo_dist_lib_dir, imago_native_libs_directory)

if sys.argv[1] == "bdist_wheel":
    for opt in sys.argv[2:]:
        if opt.startswith("--plat-name"):
            PLATFORM_NAME = opt.split("=")[1]
            if PLATFORM_NAME.startswith("macosx_10_7_intel"):
                IMAGO_LIBS = "lib/darwin-x86_64/*.dylib"
            elif PLATFORM_NAME == "manylinux1_x86_64":
                IMAGO_LIBS = "lib/linux-x86_64/*.so"
            elif PLATFORM_NAME == "manylinux1_i686":
                IMAGO_LIBS = "lib/linux-i386/*.so"
            elif PLATFORM_NAME == "win_amd64":
                IMAGO_LIBS = "lib/windows-x86_64/*.dll"
            elif PLATFORM_NAME == "mingw":
                IMAGO_LIBS = "lib/windows-x86_64/*.dll"
            elif PLATFORM_NAME == "win32":
                IMAGO_LIBS = "lib/windows-i386/*.dll"
            break

    if not IMAGO_LIBS:
        raise ValueError(
            "Wrong --plat-name value! Should be one of: macosx_10_7_intel, manylinux1_x86_64, manylinux1_i686, win_amd64, win32"
        )

    if not glob.glob(os.path.join(imago_python_directory, IMAGO_LIBS)):
        print("No native libs found for platform {}, exiting".format(PLATFORM_NAME))
        exit(0)
else:
    IMAGO_LIBS = 'lib/**/*'

if os.path.exists("build"):
    distutils.dir_util.remove_tree("build")
if os.path.exists("imago_chem.egg-info"):
    distutils.dir_util.remove_tree("imago_chem.egg-info")

setup(
    name="epam.imago",
    version="2.0.0",
    description="Imago, chemical structures optical recognition tool",
    author="EPAM Systems Life Science Department",
    author_email="lifescience.opensource@epam.com",
    maintainer="Mikhail Kviatkovskii",
    maintainer_email="Mikhail_Kviatkovskii@epam.com",
    packages=[
        "imago",
    ],
    license="Apache-2.0",
    url="https://lifescience.opensource.epam.com/imago/index.html",
    package_dir={"imago": "imago"},
    package_data={
        "imago": [
            IMAGO_LIBS,
        ]
    },
    classifiers=[_f for _f in CLASSIFIERS.split("\n") if _f],
    platforms=["Windows", "Linux", "Mac OS-X"],
    long_description=LONG_DESCRIPTION,
    long_description_content_type="text/plain",
    project_urls={
        "Bug Tracker": "https://github.com/epam/imago/issues",
        "Documentation": "https://lifescience.opensource.epam.com/imago/api/index.html",
        "Source Code": "https://github.com/epam/imago/",
    },
    download_url="https://pypi.org/project/epam.imago",
    test_suite='tests',
    install_requires=[
        'Pillow',
    ]
)
