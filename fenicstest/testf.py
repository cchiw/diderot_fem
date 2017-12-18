from firedrake import *
from init import sample,quantize
mesh = UnitSquareMesh(2,2)

V = FunctionSpace(mesh,"Lagrange",2)

f = Function(V)

f = interpolate(Expression("x[0]*x[1]",degree=2),V)

sample("testf.nrrd",f,10)
quantize("testf.nrrd","testf.png")


