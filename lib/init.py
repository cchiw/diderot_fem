
from firedrake import *
import ctypes
from firedrake.function import make_c_evaluate
from os.path import abspath, dirname
import os
from os import path
cwd = abspath(dirname(__file__))


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
    p_cf = f._ctypes
    init_file = path.join(path.dirname(__file__), '../programs/mesh_d2s_single/mesh_d2s_single_init.o')
    diderot_file = path.join(path.dirname(__file__),'../programs/mesh_d2s_single/mesh_d2s_single.o')
    call = make_c_evaluate(f, "callDiderot", ldargs=[init_file, diderot_file, "-lteem"])
    type = 1
    return call(ctypes.c_char_p(name),type,p_cf, res)

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
