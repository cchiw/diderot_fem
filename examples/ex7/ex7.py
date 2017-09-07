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

imgpath = 'data/'

def quantize(namenrrd,namepng):
    os.system('unu quantize -b 16 -i ' +namenrrd+ ' -o '+ namepng )

# init diderot program
def ex7(name, f, res, rayStep):
    init_file = 'ex7_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_ex7.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_ex7(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, rayStep)
    return(result)




## talk to fem, or femprime branches
def new_fem_k1(lbl, exp, res, size):
    l = 2
    exname = "fire_k1_s"+str(size)+"_new"
    name = lbl+"/"+exname

    #mesh = UnitCubeMesh(2,  2,2)
    mesh = CubeMesh(2,  2, 2, size)
    V = FunctionSpace(mesh, "P", 1)
    f = Function(V).interpolate(Expression(exp))
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    rayStep = float(size)/float(res)
    namepvd= name+'.pvd'
    #File(datafile+'.pvd') << f
    vis_diderot.mip_d3s_ex1(namenrrd,f, res,res,rayStep,1)
    quantize(namenrrd, namepng)
    os.system('open ' + namepng)

    #makejson(V, jsondata)
    #ex7(namenrrd, f, res, rayStep)
    #visualize result
    #quantize(namenrrd, namepng)
    #os.system('open ' + namepng)


def new_fem_k2(lbl, exp, res, size):
    l = 2
    exname = "fire_k2_s"+str(size)+"_new"
    name = lbl+"/"+exname
    
    #mesh = UnitCubeMesh(2,  2,2)
    mesh = CubeMesh(2,  2, 2, size)
    V= FunctionSpace(mesh,"P",2)
    f = Function(V).interpolate(Expression(exp))
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    rayStep = float(size)/float(res)
    namepvd= name+'.pvd'
    #File(datafile+'.pvd') << f
    vis_diderot.mip_d3s_ex1(namenrrd,f, res,res,rayStep,1)
    quantize(namenrrd, namepng)
    os.system('open ' + namepng)

    #makejson(V, jsondata)
    #ex7(namenrrd, f, res, rayStep)
    #visualize result
    #quantize(namenrrd, namepng)
    #os.system('open ' + namepng)

def new_fem_k4(lbl, exp, res, size):
    l = 2
    exname = "fire_k4_s"+str(size)+"_old"
    name = lbl+"/"+exname
    
    #mesh = UnitCubeMesh(2,  2,2)
    mesh = CubeMesh(2,  2, 2, size)
    V= FunctionSpace(mesh,"P",4)
    f = Function(V).interpolate(Expression(exp))
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    rayStep = float(size)/float(res)
    namepvd= name+'.pvd'
    #File(datafile+'.pvd') << f
    vis_diderot.mip_d3s_ex1(namenrrd,f, res,res,rayStep,1)
    quantize(namenrrd, namepng)
    os.system('open ' + namepng)

    #makejson(V, jsondata)
    #ex7(namenrrd, f, res, rayStep)
    #visualize result
    #quantize(namenrrd, namepng)
    #os.system('open ' + namepng)


sphere = "0.5- (((1-x[0])*(1-x[0]))+((1-x[1])*(1-x[1]))+((1-x[2])*(1-x[2])))"
# ret = x^2 + y^2 + z^2 - x^4 - y^4 - z^4; which_gquartic.png
gquartic = "(x[0]*x[0])+(x[1]*x[1])+(x[2]*x[2])-(x[0]*x[0]*x[0]*x[0])-(x[1]*x[1]*x[1]*x[1])-(x[2]*x[2]*x[2]*x[2])"
# ret = -(x^2 + y^2 - z*x^2 + z*y^2 + z^2 - 1); which_ccubic.png
ccubic = "-((x[0]*x[0])+(x[1]*x[1])-(x[2]*x[0]*x[0])+(x[2]*x[1]*x[1])+(x[2]*x[2]) -1)"

res  = 120
size = 10
def test_0():
    exp = gquartic
    new_fem_k1("gquartic", exp,res, size)

    
def test_1():
    exp = ccubic
    new_fem_k1("ccubic",  exp,res, size)


def test_2():
    exp = gquartic
    new_fem_k2("gquartic", exp,res, size)


def test_3():
    exp = ccubic
    new_fem_k2("ccubic", exp,res, size)


def test_4():
    exp = gquartic
    new_fem_k4("gquartic", exp,res, size)


def test_5():
    exp = ccubic
    new_fem_k4("ccubic",  exp,res, size)
