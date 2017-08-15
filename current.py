# py.test -v current.py

import sys
from firedrake import *
from os.path import abspath, dirname
import pytest
import os
from os import path
cwd = abspath(dirname(__file__))

sys.path.insert(0, 'lib/')
from init import *
from connect import *
from makejson import *



def test_ex2():
    #define a field
    exp="x[1]+x[0]"
    mesh = UnitSquareMesh(2,2)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V)
    f = interpolate(Expression(exp),V)
    name = 'out.nrrd'
    res = 100
    stepSize = 0.01
    # path to connection
    
    ######################### choose one ###################
    # old way (depends on fem branch)
    #cut_old(name, f, V,res, stepSize)
    # uses femprime branch and creates json file
    #cut_json(name, f, V,res, stepSize)
    #does not create json file
    cut_new(name, f, res)
    # two fields
    #V2= FunctionSpace(mesh,"P",degree=2)
    #g = Function(V2).interpolate(Expression(exp))
    #cut_newTwo(name, f, g, res)
test_ex2()
