from distutils.core import setup
from distutils.extension import Extension
from distutils.command.build_ext import build_ext
from Cython.Build import cythonize


import numpy

# mingw
gcc_cflags = ['-fopenmp',
              '-Wno-unused-function', '-Wno-maybe-uninitialized', '-Wno-format']
gcc_lflags = [ ]

msvc_cflags = [ '/openmp' ]
msvc_lflags = [ ]
macros = []

class build_ext_subclass(build_ext):
    def build_extensions(self):
        cc = self.compiler.compiler_type
        if cc == 'msvc':
            cflags = msvc_cflags
            lflags = msvc_lflags
        elif cc == 'mingw32' or cc=='unix':
            cflags = gcc_cflags
            lflags = gcc_lflags

        for ext in self.extensions:
            ext.extra_compile_args = cflags
            ext.extra_link_args = lflags
            ext.define_macros = macros

        build_ext.build_extensions(self)

ext_modules = [ Extension('open_nuance.tests.benchmark_ext',
                          ['open_nuance/tests/benchmark_ext.pyx'],
                          include_dirs=[numpy.get_include()]) ]

setup(name='open-nuance',
      version='0.1',
      description='Numerical algorithms for noninvasive cardiac electrophysiology',
      author='Alexander Kalinin',
      author_email='alec.kalinin@gmail.com',
      url='https://github.com/alkalinin',
      packages=['open_nuance.tests.benchmark'],
      ext_modules = cythonize(ext_modules),
      cmdclass = {'build_ext': build_ext_subclass}
)
