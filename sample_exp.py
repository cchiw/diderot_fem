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


def vis_exp(lbl, exp):
    mesh = UnitSquareMesh(2,2)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V).interpolate(Expression(exp))
    name = "samplecat_"+lbl
    res = 300
    a = cut_step(name, f, res)



def test_ex0():
    vis_exp("ex","x[0]*x[0]*(1-x[0])")
    vis_exp ("y", "x[1]")
    vis_exp ("x", "x[0]")
    vis_exp ("xsq", "x[0]*x[0]")
    vis_exp ("sinex", "sin(x[0])")
    vis_exp ("xsinex", "(x[0])*sin(x[0])")
