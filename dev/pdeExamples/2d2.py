from firedrake import *
mesh = UnitSquareMesh(4,4)
V = VectorFunctionSpace(mesh,"CG",3,dim=2)

u = TrialFunction(V)
v = TestFunction(V)
f = Function(V)
f = interpolate(Expression(["x[0]*x[0]+1","x[1]*x[1]+1"]),V)

F = inner(f,v)*dx
A = inner(grad(u[0]),grad(v[0]))*dx+inner(grad(u[1]),grad(v[1]))*dx

g = Constant([1,1])
bc = DirichletBC(V, g, (1,2,3,4))

u = Function(V)
solve(A==F,u,bc)
file = File("plot.pvd")
file << project(dot(u,u),FunctionSpace(mesh,"Lagrange",2))
