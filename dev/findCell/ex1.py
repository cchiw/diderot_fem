# field is defined as FunctionSpace(UnitSquareMesh(2,2), Lagrange(), 2);

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



imgpath = '../data/'

# init diderot program
def ex1(name, f, res, stepSize, cell):
    init_file = 'ex1_init.so'
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    _call.callDiderot_ex1.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_ex1(ctypes.c_char_p(name), cell,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, stepSize)
    return(result)

#progrm creates step size
def cut_step(name, f, res, cell):
    stepSize = 1.0/res

    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    ex1(namenrrd, f, res, stepSize, cell)
    #visualize result
    quantize(namenrrd, namepng)
    os.system('open ' + namepng)

# define field
def vis_exp(lbl, exp, cell):
    mesh = UnitSquareMesh(2,2)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V).interpolate(Expression(exp))
    name = lbl+"_cell_"+str(cell)
    res = 300
    a = cut_step(name, f, res, cell)


def iter_cells(lbl, exp):
    for i in range(8):
        vis_exp (lbl, exp, i)
    #vis_exp (lbl, exp, 0)

# init expression in field
def test_ex0():
    iter_cells ("x", "x[0]")
    iter_cells ("y", "x[1]")
    iter_cells("xsq", "x[0]*x[0]")
    iter_cells("sinex", "sin(x[0])")
    iter_cells("xsinex", "(x[0])*sin(x[0])")
    iter_cells("shift","x[0]*x[0]*(1-x[0])")
