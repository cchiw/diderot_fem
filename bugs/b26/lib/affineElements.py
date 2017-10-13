from firedrake import *
import ufl

elements = ufl.finiteelement.elementlist.ufl_elements.keys()

mesh = UnitSquareMesh(2,2)
for e in elements:
    print(e)
    try:
        V = FunctionSpace(mesh,e,4)
        c = mesh.ufl_coordinate_element()
        d = c.degree() <= 1
        fam = c.family() in  ["Discontinuous Lagrange", "Lagrange"]
        simplex = c.cell().is_simplex()
        isAffine = degree and fam and simplex
        if isAffine:
            print("Element {0} is Affine".format(e))
        else:
            print("Element {0} is not Affine".format(e))
    except:
        print("Element {0} failed".format(e))
