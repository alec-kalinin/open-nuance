# NUANCE:
#     Numerical Algorithms for Cardiac Electrophysiology
#
# Authors:
#     Alexander V. Kalinin <alec.kalinin@gmail.com>, 2012-2013
#     Laboratory 7, Institute for Information Transmission Problems RAS, 2012-2013
#
# License:
#     Redistribution and use of the source code with or without modification
#     are permitted for any scientific, research and educational purposes.
#
#     Redistribution and use of the source code with or without modification
#     are prohibited for any commercial purposes.

from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

import numpy

extra_args = ["-fopenmp", 
              "-Wno-unused-function", "-Wno-maybe-uninitialized", "-Wno-format"]
extra_macros = []
ext_modules = [ Extension("tests.cython_omp_ext", 
                          ["tests/cython_omp_ext.pyx"],
                          include_dirs=[numpy.get_include()],
                          extra_compile_args=extra_args,
                          extra_link_args=extra_args,
                          define_macros=extra_macros) ]

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules
)