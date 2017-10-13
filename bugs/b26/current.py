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


def test_ex1():
    res = 1000
    stepSize = 1.0/res 
    limit = 5#init field
    # call to init
    
    name = "cat"
    target ="ex1"
    namenrrd = name+'.nrrd'
    expf0 = "0+(-4*x[1])+(4*x[0]*x[1])+(5*x[0])+(-3*x[1]*x[1])+(5*x[1]*x[1]*x[0])+(-3*x[0]*x[0]*x[1]*x[1])+(-4*x[0]*x[0]*x[1])+(-1*x[0]*x[0])+(-3*x[1]*x[1]*x[1])+(-4*x[1]*x[1]*x[1]*x[0])+(-1*x[0]*x[0]*x[1]*x[1]*x[1])+(3*x[0]*x[0]*x[0]*x[1]*x[1]*x[1])+(-1*x[0]*x[0]*x[0]*x[1]*x[1])+(-3*x[0]*x[0]*x[0])"
    V= FunctionSpace(UnitSquareMesh(4,4),"Lagrange",degree=4)
    

    f11=interpolate(Expression("((-0.0559373021275 * 1.0 + -0.740475638673 * (x[1]) + -0.655916629937 * (x[1] * x[1]) + -1.12681744293 * (x[1] * x[1] * x[1]) + -0.321349731897 * (x[1] * x[1] * x[1] * x[1]) + -1.09602314067 * (x[1] * x[1] * x[1] * x[1] * x[1])) * 1.0 + (-0.267574839393 * 1.0 + -0.191358507085 * (x[1]) + -0.663012850156 * (x[1] * x[1]) + -0.0302095900298 * (x[1] * x[1] * x[1]) + -0.31825867737 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0]) + (-0.447382187629 * 1.0 + -0.858510221733 * (x[1]) + -1.18671553709 * (x[1] * x[1]) + -0.740602636055 * (x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0] * x[0]) + (-0.20432854339 * 1.0 + -0.929715604166 * (x[1]) + -1.47016881284 * (x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0] * x[0] * x[0]) + (-0.800096097307 * 1.0 + -0.998636580131 * (x[1]) + 0.0 * (x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0] * x[0] * x[0] * x[0]) + (-0.211933239767 * 1.0 + 0.0 * (x[1]) + 0.0 * (x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0] * x[0] * x[0] * x[0] * x[0]))"),V)

    bexpf1 = Expression("((0.587991412334 * 1.0 + 0.131440541338 * (x[1]) + 0.952534000329 * (x[1] * x[1]) + 0.295179463724 * (x[1] * x[1] * x[1]) + 0.228997989952 * (x[1] * x[1] * x[1] * x[1]) + 0.178579064386 * (x[1] * x[1] * x[1] * x[1] * x[1])) * 1.0 + (1.3792672245 * 1.0 + 0.217459060372 * (x[1]) + 1.2036856536 * (x[1] * x[1]) + 0.711459685785 * (x[1] * x[1] * x[1]) + 1.06400565039 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0]) + (1.02817329733 * 1.0 + 1.22905393402 * (x[1]) + 1.10223231216 * (x[1] * x[1]) + 1.29912160025 * (x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0] * x[0]) + (1.0707345889 * 1.0 + 0.629457225321 * (x[1]) + 1.26919606825 * (x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0] * x[0] * x[0]) + (1.49280288727 * 1.0 + 0.795755035876 * (x[1]) + 0.0 * (x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0] * x[0] * x[0] * x[0]) + (1.4781492158 * 1.0 + 0.0 * (x[1]) + 0.0 * (x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1]) + 0.0 * (x[1] * x[1] * x[1] * x[1] * x[1])) * (x[0] * x[0] * x[0] * x[0] * x[0]))")
    f21=18.3452759119
    limit = f21

    
    # Define Dirichlet boundary
    def inside(x, on_boundary):
        return on_boundary
    
    
    # Define boundary condition
    u01 = interpolate(bexpf1,V)
    bc = DirichletBC(V, u01, (1,2,3,4))
    
    # Define trial and test functions
    u = TrialFunction(V)
    v = TestFunction(V)
    
    # Define normal component, mesh size and right-hand side
    h = CellSize(V.mesh())
    h_avg = (h('+') + h('-'))/2.0
    n = FacetNormal(V.mesh())
    x = SpatialCoordinate(V.mesh())
    f = (f11) 
    
    # Penalty parameter that must be played around with
    alpha = Constant(32.0) #dependent on the mesh, I think???
    
    # Define bilinear form
    a = inner(div(grad(u)), div(grad(v)))*dx   - inner(avg(div(grad(u))), jump(grad(v), n))*dS   - inner(jump(grad(u), n), avg(div(grad(v))))*dS   + alpha/h_avg*inner(jump(grad(u),n), jump(grad(v),n))*dS
    
    
    
    # Define linear form
    L = f*v*dx
    b = assemble(L)
    
    f1=Function(V)
    solve(a == L, f1, bc)
    name = 'out'
    res = 100
    stepSize = 0.01

    a = cut_new(name, f1, res)

test_ex1()

def test_ex2():
    #define a field
    exp="x[1]*x[0]"
    mesh = UnitSquareMesh(2,2)
    V= FunctionSpace(mesh,"Lagrange",degree=2)
    f = Function(V)
    f = interpolate(Expression(exp),V)
    name = 'out'
    res = 100
    stepSize = 0.01
    # path to connection
    
    ######################### choose one ###################
    # old way (depends on fem branch)
    #cut_old(name, f, V,res, stepSize)
    # uses femprime branch and creates json file
    #cut_json(name, f, V,res, stepSize)
    #does not create json file
    a = cut_new(name, f, res)
    # two fields
    #V2= FunctionSpace(mesh,"P",degree=2)
    #g = Function(V2).interpolate(Expression(exp))
    #cut_newTwo(name, f, g, res)
#test_ex2()
