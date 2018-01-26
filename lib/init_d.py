from dolfin import *
import ctypes
from os.path import abspath, dirname
import os
from os import path
cwd = abspath(dirname(__file__))
from ctypes import POINTER, c_int, c_double, c_void_p, c_float
import numpy
import numpy.ctypeslib as npct
import time



float_type = "float64" #float or double
ctypes_float_type =  ctypes.c_double
        


#from pyop2
def as_ctypes(dtype):
    """Convert a numpy dtype like object to a ctypes type."""
    return {"bool": ctypes.c_bool,
            "int": ctypes.c_int,
            "int8": ctypes.c_char,
            "int16": ctypes.c_int16,
            "int32": ctypes.c_int32,
            "int64": ctypes.c_int64,
            "uint8": ctypes.c_ubyte,
            "uint16": ctypes.c_uint16,
            "uint32": ctypes.c_uint32,
            "uint64": ctypes.c_uint64,
            "float32": ctypes.c_float,
            "float64": ctypes.c_double}[numpy.dtype(dtype).name]


def mk_2d_array(x,t):
    # y = numpy.empty(x.shape[0],dtype=object)
    # for i in range(0,len(x)):
    #     print(x[i])
    #     y[i] = x[i].ctypes.data_as(POINTER(as_ctypes(x.dtype)))
    # return(y.ctypes.data_as(POINTER(POINTER(as_ctypes(x.dtype)))))
    #return((ctypes.cast(ctypes.c_void_p(x.ctypes.data),POINTER(POINTER(as_ctypes(c_int))))))
    return(ctypes.c_void_p(x.ctypes.data))



class _CFunction(ctypes.Structure):
    """C struct collecting data that we need"""
    _fields_ = [ ("dim",c_int),
                 ("Gdim", c_int),
                 ("Sdim", c_int),
                 ("NumCells", c_int),
                 ("GetTracker", c_void_p),
                 ("CellToNode",c_void_p),
                 ("NodeToCoords", c_void_p),
                 ("NodeToPoint", c_void_p),
                 ("Coords", POINTER(ctypes_float_type)),
                 ("Nbrs",c_void_p)] 


def organizeData(f, rdim = 1):
    func = f
    space = f.function_space()
    mesh = space.mesh()

    cellToNode = mesh.cells()
    nc = len(cellToNode)
    r = range(nc)
    nodeToPoint = mesh.coordinates()
    tempFunc = lambda x: space.dofmap().cell_dofs(x)
    coords = numpy.asfarray(f.vector().array(),dtype=float_type)

    nodeToCoords = numpy.array(list(map(lambda x: tempFunc(x), r)),dtype="int32")
    nodeToCoords= list(numpy.append(numpy.array([],dtype="int32"),list(map(lambda x: tempFunc(x), r))))
    gdim = len(cellToNode[0]) 
    sdim = len(tempFunc(0))/rdim #update for tensors?
    dim = len(space.mesh().coordinates()[0])#erm... get this somewhere?

    #sdim = len(nodeToCoords[0])

    
    import sets

    ###we need to speed this up.
    #opt3 = numpy.ones((nc,nc),dtype="int32")
    #grumble = opt3.flatten().tolist()
    opt3 = numpy.array([],dtype="int32")
    
    
    #might want to reoganizesome data



    c_data = _CFunction()
    c_data.dim = dim
    c_data.Gdim = gdim
    c_data.Sdim  = sdim
    c_data.NumCells = nc

    
    q = numpy.array([0])
    c_data.GetTracker = ctypes.cast(mk_2d_array(q.astype("int32"),c_int),c_void_p) #mk_2d_array(numpy.asfarray(numpy.array([2]),dtype="int32"),c_int)
    c_data.CellToNode = mk_2d_array(cellToNode,c_int)
    #c_data.NodeToCoords =  mk_2d_array(nodeToCoords,c_int) #nodeToPoint.ctypes.data_as(POINTER(POINTER(as_ctypes(c_int))))
    c_data.NodeToCoords =  ctypes.cast((ctypes.c_int * len(nodeToCoords))(*nodeToCoords),ctypes.c_void_p) #mk_2d_array(nodeToCoords,c_int) #nodeToPoint.ctypes.data_as(POINTER(POINTER(as_ctypes(c_int))))

    c_data.NodeToPoint = mk_2d_array(numpy.asfarray(nodeToPoint,dtype=float_type),c_int)
    
    
    functionDataCtype = reduce(lambda x,y : x*y, coords.shape, ctypes_float_type)
    functionDataSize = reduce(lambda x,y : x*y, coords.shape, 1)
    c = coords.flatten().copy()
    c_data.Coords =  ctypes.cast((ctypes_float_type*functionDataSize)(*c),POINTER(ctypes_float_type)) #c.ctypes.data_as(POINTER(ctypes_float_type))

    c_data.Nbrs = ctypes.cast((ctypes.c_int32 * (nc*nc))(*opt3),c_void_p) #This change prevented many a segfault.
    #mk_2d_array(opt3,1) #ctypes.c_void_p(opt2.ctypes.data) #mk_2d_array(opt,c_int)

    return(c_data) #pass this back
    
    


# connect to diderot programs
def data_d2s(name, f, resU, resV, stepSize):
    p_cf = f._ctypes
    init_file = path.join(path.dirname(__file__), '../programs/data_d2s/data_d2s_init.o')
    diderot_file = path.join(path.dirname(__file__),'../programs/data_d2s/data_d2s.o')
    #call = make_c_evaluate(f, "callDiderot", ldargs=[init_file, diderot_file, "-lteem"])
    # the datafile
    return call(ctypes.c_char_p(name),p_cf, resU, resV, ctypes.c_float(stepSize))


def basic_d2s_sample(name,f, resU, resV, stepSize, type):
    p_cf = f._ctypes
    init_file = path.join(path.dirname(__file__), '../programs/basic_d2s_sample/basic_d2s_sample_init.o')
    diderot_file = path.join(path.dirname(__file__),'../programs/basic_d2s_sample/basic_d2s_sample.o')
    #call = make_c_evaluate(f, "callDiderot", ldargs=[init_file, diderot_file, "-lteem"])
    type = 0
    return call(ctypes.c_char_p(name),type,p_cf, resU, resV, ctypes.c_float(stepSize))


def mesh_d2s_single(name, f, res):
    #init_file = '/home/teodoro/gitcode/diderot_fem/programs/mesh_d2s_single/mesh_d2s_single_init.so'
    init_file = '/home/teodoro/gitcode/diderot_fem/programs/mesh_d2s_single/mesh_d2s_single_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)

    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_float)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)

def single_mesh(name, f, res,init_file):
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_float)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def single_mesh_step(name, f, res,step,init_file):
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
   
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res,step)
   
    return(0)

def mesh_d2s_twofields(name, f, g, res):
    p_cf = f._ctypes
    p_cg = g._ctypes
    
    init_file = path.join(path.dirname(__file__), '../programs/mesh_d2s_twofields/mesh_d2s_twofields_init.o')
    diderot_file = path.join(path.dirname(__file__),'../programs/mesh_d2s_twofields/mesh_d2s_twofields.o')
    #call = make_c_evaluate(f, "callDiderot", ldargs=[init_file, diderot_file, "-lteem"])
    type = 1
    return call(ctypes.c_char_p(name), type, p_cf, p_cg, res)



def mesh_step(name, f, res, stepSize):
    init_file = '/Users/chariseechiw/fire/firedrake/src/firedrake/diderot_fem/programs/mesh_step/mesh_step_init.so'
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot_mesh_step.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int,ctypes.c_float)
    result = _call.callDiderot_mesh_step(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res, stepSize)
    return(result)



#visualize images
def quantize(namenrrd,namepng):
    os.system('unu quantize -b 16 -i ' +namenrrd+ ' -o '+ namepng )
    os.system('open ' + namepng)



def sample(name,f,res):
    init_file = cwd + "/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def s2dcp(name,f,res):
    init_file = cwd + "/2D-driven-cavity-p/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def s2dcvp(name,f,res):
    init_file = cwd + "/2D-driven-cavity-vpartial/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def s2dcv(name,f1,f2,res):
    init_file = cwd + "/2D-driven-cavity-v/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data1 = organizeData(f1)
    data2 = organizeData(f2)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data1),ctypes.c_void_p),ctypes.cast(ctypes.pointer(data2),ctypes.c_void_p), res)
    return(result)
def s2dcp(name,f,res):
    init_file = cwd + "/2D-driven-cavity-p/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def inside2d3(name,f,res):
    init_file = cwd + "/inside2d3/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def inside3d1(name,f,res):
    init_file = cwd + "/inside3d1/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)

def s3dcv(name,f,res):
    init_file = cwd + "/3D-driven-cavity-v/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f,rdim=3)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def s3dcvp(name,f,res):
    init_file = cwd + "/3D-driven-cavity-partialv/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def s3dcp(name,f,res):
    init_file = cwd + "/3D-driven-cavity-p/squaremesh_init.so"
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
def ridgn(name,f,res,n=1):
    init_file = cwd + "/ridg{0}/squaremesh_init.so".format(n)
    _call = ctypes.CDLL(init_file)
    data = organizeData(f)
    type = 1
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int,ctypes.c_void_p,ctypes.c_int)
    result = _call.callDiderot(ctypes.c_char_p(name), type,ctypes.cast(ctypes.pointer(data),ctypes.c_void_p), res)
    return(result)
