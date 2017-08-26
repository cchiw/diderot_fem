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

import time

imgpath = '../data/'

def quantize(namenrrd,namepng):
    os.system('unu quantize -b 16 -i ' +namenrrd+ ' -o '+ namepng )

# init diderot program
def ex5(name, f, res, rayStep):
    init_file = 'ex5_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_ex5.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_ex5(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, rayStep)
    return(result)


## create fields
def set_femex5(lbl, exp):
    l = 2
    mesh = CubeMesh(l,l,l, 2)
    V= FunctionSpace(mesh,"P",degree=2)
    f = Function(V).interpolate(Expression(exp))
    name = "ex5_"+lbl
    rayStep = 0.01
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    return (namenrrd, namepng, f, V, rayStep)



## talk to fem, or femprime branches
def new_femex52(lbl, exp, res):
    (namenrrd, namepng,  f, V, rayStep) = set_femex5(lbl, exp)
    ex5(namenrrd, f, res, rayStep)
    #visualize result
    quantize(namenrrd, namepng)
    #os.system('open ' + namepng)


#new fem with json
def new_femex51(lbl, exp, res):
    (namenrrd, namepng,  f, V, rayStep) = set_femex5(lbl, exp)
    makejson(V, jsondata)
    os.system('sh compile.sh') # compiles diderot program
    ex5(namenrrd, f, res, rayStep)
    #visualize result
    quantize(namenrrd, namepng)
#os.system('open ' + namepng)



def test_1():
    exp = "0.5- (((1-x[0])*(1-x[0]))+((1-x[1])*(1-x[1]))+((1-x[2])*(1-x[2])))"
    res  = 30
    new_femex51("newbie2_", e,res)

    print "j"

