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
from makejson import *

import ctypes
from ctypes import POINTER, c_int, c_double, c_void_p, c_float
import numpy
import numpy.ctypeslib as npct



imgpath = '../data/'

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
def old_femBase(lbl, exp, res, l):
    mesh = UnitSquareMesh(l,l)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V).interpolate(Expression(exp))
    name = "sampleexp_"+lbl

    stepSize = 1.0/res
    
    datafile = imgpath+name

    namenrrd = datafile +'.nrrd'
    type = 1
    vis_diderot.basic_d2s_sample(namenrrd,f, res, res, stepSize, type)


#progrm creates step size
def cut_step(lbl, exp, res, l):
    mesh = UnitSquareMesh(l,l)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V).interpolate(Expression(exp))
    name = "sampleexp_"+lbl

    stepSize = 1.0/res

    datafile = imgpath+name

    namenrrd = datafile +'.nrrd'
    ex1(namenrrd, f, res, stepSize)


# define field
def cut_json(lbl, exp, res,l):
    mesh = UnitSquareMesh(l,l)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V).interpolate(Expression(exp))
    name = "sampleexp_"+lbl
    stepSize = 1.0/res
    
    datafile = imgpath+name

    namenrrd = datafile +'.nrrd'
    namedata =  datafile +'.json'
    makejson(V, namedata)
    os.system('sh compile.sh')
    ex1(namenrrd, f, res, stepSize)



# init expression in field
def core(res, l):
    exp = "x[1]"

                
    start_standard = time.time()
    tmp = "\n\nres= "+str(res)+" l="+str(l)
    tmp = tmp+"\nProgram \t original fem \t Make json(time,%) \t new fem(time,%)"

    start_standardN = time.time()
    old_femBase("base_", exp, res, l)
    end_standardN = time.time()
    oldT = end_standardN - start_standardN
    tmp  = tmp+"\n base:\t "+str(oldT)
    
    start_standardN = time.time()
    cut_json("cutjson", exp, res, l)
    end_standardN = time.time()
    new1 = end_standardN  - start_standardN
    #perT = 100*((oldT- new1)/(oldT+ new1))
    tmp  = tmp+",\t "+str(new1)+"\t"#+ str(perT) +"%"
    
    start_standardN = time.time()
    cut_step("cutnew", exp,res,l)
    end_standardN = time.time()
    new2 = end_standardN  - start_standardN
    #perT = 100*((oldT- new2)/(oldT+ new2))
    tmp  = tmp+",\t "+str(new2)+"\t"#+ str(perT) +"%"


    f = open("results.txt", 'a+')
    f.write(tmp)
    f.close()


def atest_ex_res20_1():
    res = 20
    i = 2
    while (i< 100):
        core(res, i)
        i = i+2

def test_ex_res100_1():
    res = 200
    i = 2
    while (i< 50):
        core(res, i)
        i = i+2




def atest_ex_res20_2():
    res = 20
    i = 200
    while (i< 1000):
        core(res, i)
        i = i+100

def atest_ex_res100_2():
    res = 100
    i = 100
    while (i< 1000):
        core(res, i)
        i = i+100