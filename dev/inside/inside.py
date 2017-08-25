#name of data file must be the same in the diderot program and makejson call
jsondata ='data.json'

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
from makejson import *

import ctypes
from ctypes import POINTER, c_int, c_double, c_void_p, c_float
import numpy
import numpy.ctypeslib as npct



imgpath = '../data/'

# init diderot program
def inside(name, f, res, stepSize):
    init_file = 'inside_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_inside.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_inside(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, stepSize)
    return(result)

#progrm creates step size
def cut_json(name, namedata, f, V, res):
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    makejson(V, namedata)
    os.system('sh compile.sh') # compiles diderot program

    stepSize = 1.0/res
    inside(namenrrd, f, res, stepSize)
    #visualize result
    quantize(namenrrd, namepng)
    os.system('open ' + namepng)

# define field
def vis_exp(lbl, exp):
    mesh = UnitSquareMesh(2,2)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V).interpolate(Expression(exp))
    name = "inside_"+lbl
    res = 300
    a = cut_json(name, jsondata,f, V,res)


# init expression in field
def test_ex0():
    vis_exp("ex","x[0]*x[0]*(1-x[0])")
    #vis_exp ("y", "x[1]")
    #vis_exp ("x", "x[0]")
    vis_exp ("xsq", "x[0]*x[0]")
    #vis_exp ("sinex", "sin(x[0])")
    vis_exp ("xsinex", "(x[0])*sin(x[0])")

test_ex0()