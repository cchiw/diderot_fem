from firedrake import *
import tsfc
import numpy as np
import sympy as sp
import json
import re
import itertools



def makejson(V,filename):
    #Because python uses ** for float exponentiation and because numpy tries to translate this into an absurdly slow pow
    #we need to manually replace all the pow(x,int) -> x*x*x... 
    #so we bring out the regex expressions.
    search = re.compile("k\[\d+\]\*\*\d+")
    def replace_func(match):
        string = match.group(0)
        ints = re.findall("\d",string)
        newstring = "*".join(["k[{0}]".format(ints[0])]*int(ints[1]))
        return(newstring)
    def replace_powers(string):
        return(re.sub("k\[\d+\]\*\*\d+",replace_func,string))
    def replace_func_2(match):
        string = match.group(0)
        return("("+string+")")
    def float_point_protect(string):
        return(re.sub("-?\d+\.\d+e-\d+",replace_func_2,string))

    #we are going to deal with a lot of multidimensional arrays in the future and this is the best way to deal with it
    def makeIndices(shape):
        if len(shape)==1:
            return([(x,) for x in range(0,shape[0])])
        else:
            rest = makeIndices(shape[1:]) #not tail
            here = [(x,) for x in range(0,shape[0])]
            return([a+b for a in here for b in rest])

        #take a symp expression and turn it into a string that we care about
        def stringFunc(x):
            return(float_point_protect(replace_powers(str((sp.expand(x))))))

        #This must take a nparray
        def applyStringFunc(array):
            shape = array.shape
            idx = makeIndices(shape)
            new = np.empty(shape,dtype=object)
            for x in idx:
                a = stringFunc(array[x])
                new[x] = a
            return(new)
            

        dim = len(mesh.coordinates.dat.data[0]) #dimension of ground space
        #dimension of geometric function space -> number of nodes for changes of coordinates:
        gdim = len(V.mesh().coordinates.cell_node_map().values[0])
        #dimension of the function space -> number of basis functions
        sdim = len(V.coordinates.cell_node_map().values[0])
        print("The dimension is {0} with gdim {1} and sdim {2}".format(dim,gdmim,sdim))


        #geometric basis functions:
        cord_element = V.mesh().ufl_coordinate_element()
        rf = tsfc.fiatinterface.create_element(cord_element,vector_is_mixed=False)
        symbols = [[sp.Symbol("k[%d]" % i) for i in xrange(V.mesh().topological_dimension())]]
        basis1 = np.array(rf.tabulate(0, np.array(symbols))[(0,0)])
        gemBasis = applyStringFunc(basis1).flatten().tolist()

        #geometric first derivative:
        basis2 = (rf.tabulate(1, np.array(symbols)))
        geometricJacobian = (np.hstack((basis2[(1,0)],basis2[(0,1)]))) #nnodes x dim
        geometricJacobian = applyStringFunc(geometricJacobian).tolist()


        #that one point k that is in the "middle" of the reference element:
        vertex = np.array(rf.get_reference_element().get_vertices())
        centerOfRefCell = map(float,np.average(vertex, axis=0).tolist())

        #test that we need to see if we are in the refrence element
        point = tuple(sp.Symbol("newpos[%d]" % i) for i in xrange(dim))
        #credit to this one goes to the author of the diderot integration branch of firedrake:
        test = " && ".join("(%s)" % arg for arg in rf.get_reference_element().contains_point(point,epsilon=1e-14).args)

        #credit to Firedrake:
        degree = cord_element.degree() <= 1
        fam = cord_element.family() in  ["Discontinuous Lagrange", "Lagrange"]
        simplex = cord_element.cell().is_simplex()
        isAffine = degree and fam and simplex


        #space basis:
        cord_element = V.ufl_element()
        rf = tsfc.fiatinterface.create_element(cord_element,vector_is_mixed=False)
        symbols = [[sp.Symbol("k[%d]" % i) for i in xrange(V.mesh().topological_dimension())]]
        basis3 = (rf.tabulate(1, np.array(symbols)))
        temp = (basis3[(0,0)])

        spaceBasis = applyStringFunc(temp).flatten().tolist() 
        spaceJacobian = applyStringFunc(np.hstack((basis3[(1,0)],basis3[(0,1)]))).tolist()

        result =json.dumps({"dim": dim, "gdim" : gdim, "sdim" : sdim, "test": test, "isAffine": isAffine, "k": centerOfRefCell, "g_basis_functions" : gemBasis, "g_basis_dervs" : {"1": geometricJacobian}, "s_basis_functions": spaceBasis, "s_basis_dervs": {"1": spaceJacobian}},sort_keys=False,indent=4)

        with open(filename,'w+') as f:
            f.write(result)




