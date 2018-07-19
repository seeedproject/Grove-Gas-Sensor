#!/bin/sh
swig -c\+\+ -python Sensirion_common.i
python setup.py build_ext --inplace



