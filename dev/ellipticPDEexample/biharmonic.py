from firedrake import *


f1 = 0
f2 = 0 

# Create mesh and define function space
mesh = UnitSquareMesh(32, 32)
V = FunctionSpace(mesh, "CG", 2)

# Define Dirichlet boundary
def inside(x, on_boundary):
    return on_boundary


# Define boundary condition
u0 = Constant(f2)
bc = DirichletBC(V, u0, (1,2,3,4))

# Define trial and test functions
u = TrialFunction(V)
v = TestFunction(V)

# Define normal component, mesh size and right-hand side
h = CellSize(mesh)
h_avg = (h('+') + h('-'))/2.0
n = FacetNormal(mesh)
x = SpatialCoordinate(V.mesh())
f = Constant(f1) #interpolate(Expression("(x[0]*x[0]+x[1]*x[1])*(x[0]*x[0]+x[1]*x[1])"),V)

# Penalty parameter that must be played around with
alpha = Constant(8.0) #dependent on the mesh, I think???

# Define bilinear form
a = inner(div(grad(u)), div(grad(v)))*dx \
  - inner(avg(div(grad(u))), jump(grad(v), n))*dS \
  - inner(jump(grad(u), n), avg(div(grad(v))))*dS \
  + alpha/h_avg*inner(jump(grad(u),n), jump(grad(v),n))*dS




# Define linear form
L = f*v*dx
b = assemble(L)
# Solve variational problem
u = Function(V)

solve(a == L, u, bc) #solver_parameters={'ksp_type': 'cg'}

# Save solution to file
#file = File("biharmonic.pvd")
#file << u

# Plot solution
#plot(u, interactive=True)
