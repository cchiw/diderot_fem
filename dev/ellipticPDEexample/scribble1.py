from firedrake import *
import numpy as np
import sympy as sp
n = 5
dim = 2 
mesh = UnitSquareMesh(n,n)
V = FunctionSpace(mesh,"Lagrange",4)

v = TestFunction(V)
u = TrialFunction(V)

A = (u.dx(0).dx(0) + u.dx(1).dx(1))*(v.dx(0).dx(0) + v.dx(1).dx(1))*dx
f1 = Constant(0)
f2 = Constant(0)

F = f1*v*dx


