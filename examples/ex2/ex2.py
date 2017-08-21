# py.test -v sample_helm.py

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



#progrm creates step size
def cut_step(name, f, res):
    stepSize = 1.0/res
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    mesh_step(namenrrd, f, res, stepSize)
    #visualize result
    quantize(namenrrd, namepng)
    os.system('open ' + namepng)


def vis_helm():
    mesh = UnitSquareMesh(10, 10)#original
    #V = FunctionSpace(mesh, "CG", 3)
    V = FunctionSpace(mesh, "Lagrange", 3)
    u = TrialFunction(V)
    v = TestFunction(V)
    f = Function(V)
    f.interpolate(Expression("(1+8*pi*pi)*cos(x[0]*pi*2)*cos(x[1]*pi*2)"))
    a = (dot(grad(v), grad(u)) + v * u) * dx
    L = f * v * dx
    u = Function(V)
    solve(a == L, u, solver_parameters={'ksp_type': 'cg'})
    #solve(a == L, u, solver_parameters={'ksp_type': 'Lagrange'})
    name = "helm"
    res = 100
    a = cut_step(name, u, res)


vis_helm()