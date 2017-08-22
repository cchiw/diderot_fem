from firedrake import *
maxn = 16
outfile1 = File("output1.pvd")
outfile2 = File("output2.pvd")


for x in range(1,maxn+1):
    for y in range(1,maxn+1):
        mesh = UnitSquareMesh(x,y)
        V = FunctionSpace(mesh,"Lagrange",5)
        f = Function(V)
        f.interpolate(Expression("sin(x[0]*40.0)*1.0/1600.0+cos(x[1]*80.0)*1.0/1600.0",V))
        outfile1 = File("pvd/output{0}.pvd".format(16*(x-1)+y))
        outfile1.write(f)
        if x==y:
            outfile2 = File("pvd/output.{0}.pvd".format(x))
            outfile2.write(f)

