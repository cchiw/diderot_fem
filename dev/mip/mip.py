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

# init diderot program
def mip(name, f, res, rayStep):
    init_file = 'mip_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_mip.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_mip(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, rayStep)
    return(result)



def set_fem(lbl, exp):
    mesh = CubeMesh(2, 2,2, 2)
    V= FunctionSpace(mesh,"P",degree=3)
    f = Function(V).interpolate(Expression(exp))
    name = "mip_"+lbl
    res = 100
    rayStep = 0.01
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    return (namenrrd, namepng, f, res, rayStep)

#uses new femprime branches
def new_fem(lbl, exp):
    (namenrrd, namepng,  f, res, rayStep) = set_fem(lbl, exp)
    #makejson(V, namedata)
    #os.system('sh compile.sh') # compiles diderot program
    mip(namenrrd, f, res, rayStep)
    #visualize result
    quantize(namenrrd, namepng)
    os.system('open ' + namepng)


# uses old fem branch
def old_fem(lbl, exp):
    (namenrrd, namepng,  f, res, rayStep) = set_fem(lbl, exp)
    vis_diderot.mip_d3s_ex1(namenrrd,f,res,res,rayStep, 1)
    quantize(namenrrd,namepng)
    os.system('open ' + namepng)

def attempt_all(name, exps, callfn):
    i = 0
    start_standard = time.time()
    for e in exps:
        callfn(name+str(i), e)
        i=i+1
    end_standard = time.time()
    tt_standard  = "\n"+name+":"+str(end_standard  - start_standard )
    print (tt_standard )
    f = open("results.txt", 'a+')
    f.write( tt_standard)
    f.close()


# init expression in field
def test_ex0():
    expA="x[0]"
    expB="x[0]*x[0]*x[0]"
    expC="sin(x[0])"
    expD="x[0]*x[0]*(1-x[0])"
    expE="0.5- (((1-x[0])*(1-x[0]))+((1-x[1])*(1-x[1]))+((1-x[2])*(1-x[2])))"
    exps = [expA, expB, expC, expD, expE]


    attempt_all("newbie", exps, new_fem)
    attempt_all("base", exps, old_fem)