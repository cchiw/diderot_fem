# field is defined as FunctionSpace(UnitSquareMesh(2,2), Lagrange(), 2);

import sys
from firedrake import *
from os.path import abspath, dirname
import pytest
import os
from os import path
cwd = abspath(dirname(__file__))

sys.path.insert(0, '../../../lib/')
from init import *
#from connect import *
#from makejson import *

import ctypes
from ctypes import POINTER, c_int, c_double, c_void_p, c_float
import numpy
import numpy.ctypeslib as npct



imgpath = '../../../data/'

# init diderot program
def ex1(name, f, res, stepSize):
    init_file = "/home/teodoro/gitcode/diderot_fem/examples/vis_failure/1/one_init.so" #We can calculate absolute path.
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_one.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_one(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, stepSize)
    return(result)

#progrm creates step size
def cut_step(name, f, res):
    stepSize = 1.0/res

    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    ex1(namenrrd, f, res, stepSize)
    #visualize result
    quantize(namenrrd, namepng)
    os.system('open ' + namepng)

# define field
def vis_exp(lbl, exp):
    mesh = UnitSquareMesh(8,8)
    V= FunctionSpace(mesh,"Lagrange",degree=5)
    f = Function(V).interpolate(Expression(exp))
    name = "sampleexp_"+lbl
    res = 3000
    a = cut_step(name, f, res)


# init expression in field
def test_ex0():
    #vis_exp("ex","x[0]*x[0]*(1-x[0])")
    vis_exp ("erg", "sin(x[0]*40.0)*1.0/1600.0+cos(x[1]*80.0)*1.0/1600.0")
    #vis_exp ("x", "x[0]")
    #vis_exp ("xsq", "x[0]*x[0]")
    #vis_exp ("sinex", "sin(x[0])")
    #vis_exp ("xsinex", "(x[0])*sin(x[0])")

test_ex0()
