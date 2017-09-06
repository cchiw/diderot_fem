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
def ex4(name, f, res, stepSize):
    init_file = 'ex4_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_ex4.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_ex4(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, stepSize)
    return(result)

#progrm creates step size
def cut_json(name, namedata, f, V, res):
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    os.system(' rm '+namedata)
    makejson(V, namedata)
    os.system('sh compile.sh') # compiles diderot program

    stepSize = 1.0/res
    print " Res: ", res, "stepsize: ", stepSize
    ex4(namenrrd, f, res, stepSize)
    #visualize result
    quantize(namenrrd, namepng)

    os.system('rm '+namedata)
    os.system('rm '+namenrrd)

#vis helm holtz
def test_helm_k2():
    name = "helm_n30_k1_r200"
    mesh = UnitSquareMesh(10, 10)
    V = FunctionSpace(mesh, "CG", 1)
    
    u = TrialFunction(V)
    v = TestFunction(V)
    f = Function(V)
    f.interpolate(Expression("(1+8*pi*pi)*cos(x[0]*pi*2)*cos(x[1]*pi*2)"))
    a = (dot(grad(v), grad(u)) + v * u) * dx
    L = f * v * dx
    u = Function(V)
    solve(a == L, u, solver_parameters={'ksp_type': 'cg'})
    a = cut_json(name, jsondata, u, V, 200)





