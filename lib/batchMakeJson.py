from makejson import makejson
from firedrake import *


spath = "../fnspace_data/"

meshes = [(UnitSquareMesh(1,1),"UnitSquareMesh"),(UnitCubeMesh(1,1,1),"UnitCubeMesh"), (SquareMesh(1,1,1),"SquareMesh")]
#The number of cells in the mesh does not matter and neither does the location in space
#-> we only want the refrence element with the mesh, not the mesh itself.
elements = ["Lagrange","P"]
degrees = [1,2,3]

for m in meshes:
    for e in elements:
        for d in degrees:
            V = FunctionSpace(m[0],e,degree=d)
            path = spath+m[1]+"_"+e+"_"+str(d)+".json"
            print(path)
            makejson(V,path)
