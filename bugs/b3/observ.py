
import sys
from firedrake import *
from os.path import abspath, dirname
import pytest
import os
from os import path
cwd = abspath(dirname(__file__))
sys.path.insert(0, '../../lib/')

from init import *
#from connect import *
#from makejson import *

import ctypes
from ctypes import POINTER, c_int, c_double, c_void_p, c_float
import numpy
import numpy.ctypeslib as npct





# init diderot program
# two fields
def init2(name, f, g,target):
    init_file = target+'_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    dataF = organizeData(f)
    dataG = organizeData(g)
    _call.callDiderot_observ.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_void_p)
    result = _call.callDiderot_observ(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(dataF),ctypes.c_void_p),ctypes.cast(ctypes.pointer(dataG),ctypes.c_void_p))
    return(result)


#compiles program
os.system("make clean ")
os.system("make obsev.o ")
os.system("make observ_init.o ")
os.system("make observ_init.so ")
##############################################

#init field

name = "cat"
target ="observ"
namenrrd = name+'.nrrd'
expf0 = "0+(2*1)"
mesh = UnitSquareMesh(2,2)
V= FunctionSpace(mesh,"Lagrange",degree=2)
f0 = Function(V).interpolate(Expression(expf0))
expf1 = ("0+(2*1)+(5*x[1])","0+(2*1)+(5*x[1])+(2*1)+(2*x[1])")
mesh = UnitSquareMesh(2,2)
V= FunctionSpace(mesh,"Lagrange",degree=2, dim = 2)
f1 = Function(V).interpolate(Expression(expf1))
init2(namenrrd, f0, f1,  target)