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
def mip(name, f, res, rayStep):
    init_file = 'mip_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_mip.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_mip(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, rayStep)
    return(result)


## create fields
def set_femMip(lbl, exp, l, k):
    mesh = CubeMesh(l,l,l, 2)
    V= FunctionSpace(mesh,"P",degree=3)
    f = Function(V).interpolate(Expression(exp))
    name = "mip_"+lbl
    rayStep = 0.01
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    return (namenrrd, namepng, f, V, rayStep)



## talk to fem, or femprime branches
def new_femMip2(lbl, exp, res, l, k):
    (namenrrd, namepng,  f, V, rayStep) = set_femMip(lbl, exp, l, k)
    #makejson(V, namedata)
    #os.system('sh compile.sh') # compiles diderot program
    mip(namenrrd, f, res, rayStep)
    #visualize result
    quantize(namenrrd, namepng)
    #os.system('open ' + namepng)


#new fem with json
def new_femMip1(lbl, exp, res, l, k):
    (namenrrd, namepng,  f, V, rayStep) = set_femMip(lbl, exp, l, k)
    makejson(V, jsondata)
    os.system('sh compile.sh') # compiles diderot program
    mip(namenrrd, f, res, rayStep)
    #visualize result
    quantize(namenrrd, namepng)
#os.system('open ' + namepng)

# uses old fem branch
def old_femMip(lbl, exp, res, l, k):
    (namenrrd, namepng,  f, V, rayStep) = set_femMip(lbl, exp, l, k)
    vis_diderot.mip_d3s_ex1(namenrrd,f,res,res,rayStep, 1)
    quantize(namenrrd,namepng)
    #os.system('open ' + namepng)



def attempt_all(exps, res, l,k):
    start_standard = time.time()
    tmp = "\n\nres= "+str(res)+" l="+str(l)+" k="+str(k)
    tmp = tmp+"\nProgram \t original fem \t Make json(time,%) \t new fem(time,%)"
    for (expname, e) in exps:
        start_standardN = time.time()
        old_femMip("base_"+expname, e, res,l,k)
        end_standardN = time.time()
        oldT = end_standardN - start_standardN
        tmp  = tmp+"\n"+expname+":\t "+str(oldT)

    
        start_standardN = time.time()
        new_femMip1("newbie1_"+expname, e,res,l,k)
        end_standardN = time.time()
        new1 = end_standardN  - start_standardN
        #perT = 100*((oldT- new1)/(oldT+ new1))
        tmp  = tmp+",\t "+str(new1)+",\t"#+ str(perT) +"%"
        
        start_standardN = time.time()
        new_femMip2("newbie2_"+expname, e,res,l,k)
        end_standardN = time.time()
        new2 = end_standardN  - start_standardN
        #perT = 100*((oldT- new2)/(oldT+ new2))
        tmp  = tmp+",\t "+str(new2)+",\t"#+ str(perT) +"%"

    f = open("results.txt", 'a+')
    f.write(tmp)
    f.close()

# init expression in field
expA=("linear", "x[0]")
expB=("cube1", "x[0]*x[0]*x[0]")
expC=("trig", "sin(x[0])")
expD=("cube2", "x[0]*x[0]*(1-x[0])")
expE=("circle","0.5- (((1-x[0])*(1-x[0]))+((1-x[1])*(1-x[1]))+((1-x[2])*(1-x[2])))")
exps = [expE]

#base line
res = 20
l =2
k = 3
#different tests


def atest_res_20():
    attempt_all(exps, 20, l, k)

def atest_discret_10():
    attempt_all(exps, res, 3, k)

def atest_discret_5():
    attempt_all(exps, res, 5, k)
def atest_discret_10():
    attempt_all(exps, res, 10, k)
def test_higher_l20():
    attempt_all(exps, res, 20, k)
def atest_res_10():
    attempt_all(exps, 10, l, k)

def atest_res_50():
    attempt_all(exps, 50, l, k)
def test_higher_l50():
    attempt_all(exps, res, 50, k)
def test_higher_r100():
    attempt_all(exps, 100, l, k)


def test_higher_r200():
    attempt_all(exps, 200, l, k)
def test_higher_r300():
    attempt_all(exps, 300, l, k)