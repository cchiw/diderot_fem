# py.test -v sample.py

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



def test_ex0():

    exp= "x[0]*x[0]*(1-x[0])"
    #exp = "x[1]"
    
    mesh = UnitSquareMesh(2,2)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V).interpolate(Expression(exp))
    name = "samplecat100_cut2+"
    res = 100
    stepSize = 0.01

    a = cut_step(name, f, res, stepSize)
    
test_ex0()