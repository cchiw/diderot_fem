
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
# single field
def init1(name, f,target):
    init_file = target+'_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_observ.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p)
    result = _call.callDiderot_observ(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p))
    return(result)


##############################################
#general declarations
#init field
# call to init
#compiles program
os.system("make clean ")
os.system("make obsev.o ")
os.system("make observ_init.o ")
os.system("make observ_init.so ")
name = "cat"
target ="observ"
namenrrd = name+'.nrrd'
expf0 = "0+(2*1)+(-3*x[1])+(5*x[0]*x[1])+(4*x[0])+(4*x[1]*x[1])+(-5*x[1]*x[1]*x[0])+(-2*x[0]*x[0]*x[1]*x[1])+(2*x[0]*x[0]*x[1])+(1*x[0]*x[0])+(3*x[1]*x[1]*x[1])+(-3*x[1]*x[1]*x[1]*x[0])+(-4*x[0]*x[0]*x[0]*x[1]*x[1])+(-2*x[0]*x[0]*x[0]*x[1])+(-3*x[0]*x[0]*x[0])+(4*1*x[2])+(-5*x[1]*x[2])+(2*x[0]*x[1]*x[2])+(-5*x[0]*x[2])+(-3*x[0]*x[0]*x[1]*x[1]*x[2])+(5*x[0]*x[0]*x[1]*x[2])+(-2*x[0]*x[0]*x[2])+(-4*x[1]*x[1]*x[1]*x[2])+(2*x[1]*x[1]*x[1]*x[0]*x[2])+(2*x[0]*x[0]*x[1]*x[1]*x[1]*x[2])+(3*x[0]*x[0]*x[0]*x[1]*x[1]*x[1]*x[2])+(4*x[0]*x[0]*x[0]*x[1]*x[1]*x[2])+(-4*x[0]*x[0]*x[0]*x[1]*x[2])+(-5*x[0]*x[0]*x[0]*x[2])+(2*1*x[2]*x[2])+(-5*x[1]*x[2]*x[2])+(-4*x[0]*x[1]*x[2]*x[2])+(3*x[0]*x[2]*x[2])+(2*x[1]*x[1]*x[2]*x[2])+(-1*x[1]*x[1]*x[0]*x[2]*x[2])+(-3*x[0]*x[0]*x[1]*x[1]*x[2]*x[2])+(1*x[0]*x[0]*x[1]*x[2]*x[2])+(1*x[0]*x[0]*x[2]*x[2])+(-5*x[1]*x[1]*x[1]*x[2]*x[2])+(-5*x[1]*x[1]*x[1]*x[0]*x[2]*x[2])+(2*x[0]*x[0]*x[1]*x[1]*x[1]*x[2]*x[2])+(2*x[0]*x[0]*x[0]*x[1]*x[1]*x[1]*x[2]*x[2])+(-1*x[0]*x[0]*x[0]*x[1]*x[1]*x[2]*x[2])+(-3*x[0]*x[0]*x[0]*x[1]*x[2]*x[2])+(-4*x[0]*x[0]*x[0]*x[2]*x[2])"
V= FunctionSpace(UnitCubeMesh(3,3,3),"P",degree=4)
f0 = Function(V).interpolate(Expression(expf0))
init1(namenrrd, f0,  target)