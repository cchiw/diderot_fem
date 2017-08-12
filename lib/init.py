
from firedrake import *
import ctypes
from firedrake.function import make_c_evaluate
from os.path import abspath, dirname
import os
from os import path
cwd = abspath(dirname(__file__))
from ctypes import POINTER, c_int, c_double, c_void_p, c_float
import numpy

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



class _CFunction(ctypes.Structure):
    """C struct collecting data that we need"""
    _fields_ = [("Gdim", c_int),
                ("Sdim", c_int),
                ("NumCells", c_int),
                ("CellToNode", POINTER(c_int)),
                ("NodeToCoords", POINTER(as_ctypes(c_int))),
                ("NodeToPoint", POINTER(as_ctypes(c_float))),
                ("Coords", POINTER(c_float))] 


def organizeData(f):
    func = f
    space = f.function_space()
    mesh = space.mesh()

    cellToNode = mesh.coordinates.cell_node_map().values
    nodeToPoint = mesh.coordinates.dat.data
    nodeToCoords = V.cell_node_map().values
    coords = f.dat.data

    gdim = 2 #could be 3
    sdim = len(nodeToCoords[0])
    #might want to reoganize some data
    c_data = _CFunction()
    c_data.Gdim = gdim
    c_data.Sdim  = sdmin
    c_data.NumCells = len(coord)
    c_data.CellToNode = cellToNode.data_as(POINTER(as_ctypes(c_float)))
    c_data.NodeToCoords = nodeToPoint.data_as(POINTER(as_ctypes(c_float)))
    c_data.NodeToPoint = nodeToCoords.data_as(POINTER(as_ctypes(c_float)))
    c_data.Coords =  coords.data_as(POINTER(as_ctypes(c_float)))
    return(c_data) #pass this back
    
    


# connect to diderot programs
def data_d2s(name, f, resU, resV, stepSize):
    p_cf = f._ctypes
    init_file = path.join(path.dirname(__file__), '../programs/data_d2s/data_d2s_init.o')
    diderot_file = path.join(path.dirname(__file__),'../programs/data_d2s/data_d2s.o')
    call = make_c_evaluate(f, "callDiderot", ldargs=[init_file, diderot_file, "-lteem"])
    # the datafile
    return call(ctypes.c_char_p(name),p_cf, resU, resV, ctypes.c_float(stepSize))


def basic_d2s_sample(name,f, resU, resV, stepSize, type):
    p_cf = f._ctypes
    init_file = path.join(path.dirname(__file__), '../programs/basic_d2s_sample/basic_d2s_sample_init.o')
    diderot_file = path.join(path.dirname(__file__),'../programs/basic_d2s_sample/basic_d2s_sample.o')
    call = make_c_evaluate(f, "callDiderot", ldargs=[init_file, diderot_file, "-lteem"])
    type = 0
    return call(ctypes.c_char_p(name),type,p_cf, resU, resV, ctypes.c_float(stepSize))


def mesh_d2s_single(name, f, res):
    stepSize = 0.1
    p_cf = f._ctypes
    init_file = '/home/teodoro/gitcode/diderot_fem/programs/mesh_d2s_single/mesh_d2s_single_init.so'
    diderot_file = path.join(path.dirname(__file__),'../programs/mesh_d2s_single/mesh_d2s_single.o')
    #call = make_c_evaluate(f, "callDiderot", ldargs=[init_file, diderot_file, "-lteem"])
    _call = ctypes.CDLL(init_file)
    type = 1
    data = organizeData(f)
    _call.callDiderot.argtypes = (ctypes.c_char_p,ctypes.c_int, ctypes.POINTER(ctypes.c_int),ctypes.c_float(stepSize))
    args = (ctypes.c_char_p(name), 1,data, res)
    result = _call.callDiderot(args)
    print "Probably worked"
    return(result)

def mesh_d2s_twofields(name, f, g, res):
    p_cf = f._ctypes
    p_cg = g._ctypes
    
    init_file = path.join(path.dirname(__file__), '../programs/mesh_d2s_twofields/mesh_d2s_twofields_init.o')
    diderot_file = path.join(path.dirname(__file__),'../programs/mesh_d2s_twofields/mesh_d2s_twofields.o')
    call = make_c_evaluate(f, "callDiderot", ldargs=[init_file, diderot_file, "-lteem"])
    type = 1
    return call(ctypes.c_char_p(name), type, p_cf, p_cg, res)



#visualize images
def quantize(namenrrd,namepng):
    os.system('unu quantize -b 8 -i ' +namenrrd+ ' -o '+ namepng)
    os.system('open ' + namepng)
