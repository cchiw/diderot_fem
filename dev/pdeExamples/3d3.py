from firedrake import *

#See https://www.cs.cmu.edu/~12-759/elasticity.pdf for details

def eps(u):
    a = 0.5*(nabla_grad(u)+nabla_grad(u).T)
    return(a)

def sig(u,l):
    a = 2*eps(u)+l*div(u)*Identity(3)
    return(a)

mesh = UnitCubeMesh(4,4,4)
V = VectorFunctionSpace(mesh,"Lagrange",3)

u = TrialFunction(V)
v = TestFunction(V)
#displacement = as_vector([0,0,0])
body_force = as_vector([3,2,1])
f = Function(V)
f = body_force

hmm = sig(u,0.5)
a = inner(hmm,eps(v))*dx
F = dot(f,v)*dx 
u = Function(V)
bc = DirichletBC(V,Constant((0,0,0)),(1,2,3,4))

solve(a==F,u,bc)

file = File("plot.pvd")
file << project(dot(u,u),FunctionSpace(mesh,"Lagrange",3))
