from firedrake import *
# mesh = UnitSquareMesh(1,1)
# V = FunctionSpace(mesh,"Lagrange",6)
# f = Function(V)
# f = interpolate(Expression("x[0]*x[1]"),V)
# W = FunctionSpace(mesh,"Lagrange",1)
# g = Function(W)
# g = project(f,W)
# f.at((0.5,0.5))
# projected = File("picture.pvd")
# projected.write(f)

mesh = UnitSquareMesh(4, 4)
V = FunctionSpace(mesh, "Lagrange", 1)
f = Function(V)
f.interpolate(sin(SpatialCoordinate(mesh)[0]))

outfile = File("output.pvd")
outfile.write(f)
