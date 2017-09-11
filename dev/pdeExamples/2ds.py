from firedrake import *
mesh = UnitSquareMesh(4,4)
V = FunctionSpace(mesh,"Lagrange",3)

u = TrialFunction(V)
v = TestFunction(V)
f = Function(V)

f = interpolate(Expression("x[0]*x[1]+x[0]+x[1]"),V)
g = Constant(0)


#non max principle ellipic pde in 2 variables
L = 5*u.dx(0)*v.dx(0)*dx + 10*u.dx(1)*v.dx(1)*dx  + 1*u.dx(1)*v.dx(0)*dx +1*u.dx(0)*v.dx(1)*dx + 1*u.dx(0)*v*dx + 1*u.dx(1)*v*dx + 2*u*v*dx
F = f*v*dx

bc = DirichletBC(V, g, (1,2,3,4))
u = Function(V)

solve(L==F,u,bc)

file = File("plot.pvd")
file << u

#Plot solution
#plot(u, interactive=True)
