from firedrake import *
import ufl
import numpy as np

meshes = []
elements = []

listOfMeshes = utility_meshes.__all__

def g(f,i):
    try:
        return(f(*i))
    except:
        return(None)

    
for m in listOfMeshes:
    if m == "CircleManifoldMesh":
        continue
    tries = []
    meshFunc = getattr(utility_meshes,m)
    for x in range(0,7):
        i = tuple(np.repeat(3,x))
        t = g(meshFunc,i)
        if t != None:
            tries.append(t)
    if tries == []:
        print(m)
    else:
        meshes.append(tries[0])


elementDict = ufl.finiteelement.elementlist.ufl_elements
listOfelements = ufl.finiteelement.elementlist.ufl_elements.keys()

for e in listOfelements:
    sobSpace = elementDict[e][3]
    if not(("HCurl" in str(sobSpace)) or ("HDiv" in str(sobSpace)) or ("HDivDiv" in str(sobSpace))):
        elements.append(e)

dm = []
de = []
pairs = []

for m in meshes:
    for e in elements:
        try:
            V = FunctionSpace(m,e,3) #issue of what is a valid order for some elements
            f = Function(V)
            f = interpolate(Expression("1",V),V)
            try:
                f.at(0)
                pairs.append((m,e))
            except:
                pass

        except:
            pass
            
    

print(pairs)



#we need to elimiate all extruded and mixed options!


