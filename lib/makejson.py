from firedrake import *
import tsfc
import numpy as np
import sympy as sp
import json
import re
import itertools



def makejson(V,filename):
#Example input:
#Taken from https://stackoverflow.com/questions/14264431/expanding-algebraic-powers-in-python-sympy but useless
# def pow_to_mul(expr):
#     """
#     Convert integer powers in an expression to Muls, like a**2 => a*a.
#     """
#     pows = list(expr.atoms(sp.Pow))
#     if any(not e.is_Integer for b, e in (i.as_base_exp() for i in pows)):

#         raise ValueError("A power contains a non-integer exponent")
#     #repl = zip(pows, (Mul(*list([b]*e for b, e in i.as_base_exp()), evaluate=False) for i in pows))
#     repl = zip(pows, (sp.Mul(*[b]*e,evaluate=False) for b,e in (i.as_base_exp() for i in pows)))
#     return expr.subs(repl)



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



        #for use later:
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
        nnodes = len(V.mesh().coordinates.cell_node_map().values[0]) #number of nodes per element


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

        #test:
        point = tuple(sp.Symbol("newpos[%d]" % i) for i in xrange(dim))
        #credit to this one goes to the author of the diderot integration branch of firedrake:
        test = " && ".join("(%s)" % arg for arg in rf.get_reference_element().contains_point(point,epsilon=1e-14).args)

        # # #isAffine = cord_element.is_simplex() and cord_element.degree() <= 1 and cord_element.family() in ["Discontinuous Lagrange", "Lagrange"]
        # # #FIX ME^
        #credit as above:
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
        spaceBasis = applyStringFunc(temp).flatten().tolist() #some verification needs to happen here


        spaceJacobian = applyStringFunc(np.hstack((basis3[(1,0)],basis3[(0,1)]))).tolist()


        result =json.dumps({"dim": dim, "nnodes" : nnodes, "test": test, "isAffine": isAffine, "k": centerOfRefCell, "basis_functions" : gemBasis, "basis_dervs" : {"1": geometricJacobian}, "eval_basis": spaceBasis, "eval_dervs": {"1": spaceJacobian}},sort_keys=False,indent=4)

        with open(filename,'w+') as f:
            f.write(result)




