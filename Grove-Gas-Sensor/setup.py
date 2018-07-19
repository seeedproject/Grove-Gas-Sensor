#!/usr/bin/env python

""""
setup.py file for SWIG C\+\+/Python MutichannelGasSensor
"""

from distutils.core import setup,Extension
Sensirion_module = Extension('_Sensirion',
                          sources=['sensirion_common.cpp',
						  'sensirion_configuration.cpp',
						  'sgp30.cpp',
						  'sgp30_featureset.c',
						  'i2crw.cpp','Sensirion_common_wrap.cxx',],
                          )

setup (name = 'Sensirion',
        version = '0.1',
        author = "www.seeed.com",
        description = """ C\+\+/Python GasSensor""",
        ext_modules = [Sensirion_module],
        py_modules = ["Sensirion"],
        )