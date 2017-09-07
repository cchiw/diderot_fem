from firedrake import *
import numpy as np
import sympy as sp
n = 5
dim = 2 
mesh = UnitSquareMesh(n,n)
V = FunctionSpace(mesh,"Lagrange",4)


def testPosDef(x):
    return np.all(np.linalg.eigvals(x) > 0)

def isSym(x):
    return((A==A.T).all())

shape = (dim,dim)

A = np.empty(shape,dtype="float")

#fill in A:
A[0][0]= 5
A[1][1]= 10
A[0][1] = 1
A[1][0]= 1


if not((testPosDef(A) and isSym(A))):
    print("Matrix A not acceptable for Ellitpic PDE")
    exit(1)

A1 = np.empty(shape,dtype="object")    



for s in np.ndindex(shape):
    A1[s[0]][s[1]]= Constant(A[s[0]][s[1]])



b = range(dim)

#fill in B
b[0] = 1
b[1] = 2
b1 = np.array(map(Constant,b))

#fill in c!
c = 0
c1 = Constant(c)


#make the PDE:
v = TestFunction(V)
u = TrialFunction(V)

for s in np.ndindex(shape):
    A1[s[0]][s[1]] = u.dx(s[0])*v.dx(s[1])*A1[s[0]][s[1]]*dx

for s in range(dim):
    b1[s] = b1[s]*u.dx(s)*v*dx


c1 = c1*u*v*dx

L = sum(sum(A1))+sum(b1)+c1

print(L)

f = Function(V)
f = interpolate(Expression("0"),V)
F = f*v*dx

form = L-F

bterm = Constant(0)
def boundary(x, on_boundary):
    return on_boundary

bc = DirichletBC(V,bterm,boundary)

solve(form==0,u,bc)








