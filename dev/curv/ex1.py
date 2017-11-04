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



imgpath = ''#'../data/'

# init diderot program
def ex1(name, f, res, stepSize):
    init_file = 'ex1_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_ex1.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_ex1(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, stepSize)
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
    mesh = UnitCubeMesh(2,2,2)
    V= FunctionSpace(mesh,"P",degree=4)
    f = Function(V).interpolate(Expression(exp))
    name = "curv_"+lbl
    res = 200
    a = cut_step(name, f, res)


# init expression in field
def test_ex0():

    exp1 = "x[1]"
    vis_exp("y",exp1)
    exp2 = "x[0]*x[0] + x[1]*x[1] + x[2]*x[2] - x[0]*x[0]*x[0]*x[0]- x[1]*x[1]*x[1]*x[1]-x[2]*x[2]*x[2]*x[2]"#gquartic
    vis_exp("gquartic",exp2)
    exp3 = "-(x[0]*x[1] + x[1]*x[1] - x[2]*x[0]*x[0] + x[2]* x[1]*x[1]  +  x[2]*x[2] - 1"#ccubic
    vis_exp("ccubic",exp3)
    exp4= "0.5- (((1-x[0])*(1-x[0]))+((1-x[1])*(1-x[1]))+((1-x[2])*(1-x[2])))"

    vis_exp ("sphere", exp4)

test_ex0()