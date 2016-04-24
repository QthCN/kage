from distutils.core import setup, Extension

import numpy as np

EXTRA_COMPILE_ARGS = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.8']
EXTRA_LINK_ARGS = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.8']

kageext_module = Extension('kageext',
                           sources=['src/kageext.cpp', 'src/datarobot2d.cpp', 'src/utils.cpp'],
                           include_dirs=[np.get_include()],
                           extra_compile_args=EXTRA_COMPILE_ARGS,
                           extra_link_args=EXTRA_LINK_ARGS)

REQUIRES = ['nose (>=1.3.0)']

setup(name='Kage',
      version='1.0',
      description='Kage',
      author='Qin TianHuan',
      author_email='tianhuan@bingotree.cn',
      packages=['kage'],
      ext_modules=[kageext_module],
      requires=REQUIRES)
