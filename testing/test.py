import random
import sys
from firedrake import *
import numpy as np
from os.path import abspath, dirname
import pytest
import os
import select
from os import path
cwd = abspath(dirname(__file__))

sys.path.insert(0, '../lib/')
from connect import *

#Step 1: figure out example and points
#step 2: diderot file
#Step 3: compile diderot file
#Step 4: run and import results
#Step 5: check results


pyfile = """



#random data
data = {0}

#solve the pde: has a function f
{1}


ff = lambda x: f.at(x)

name = "out"
res = 100
so = {2}
single_mesh(name, f, res,so)

for x in data:
\tprint(ff(x))
"""

def run_test(mesh,meshname,element,dim,bounds, degree,npoints):
    V = FunctionSpace(mesh,element,degree=degree)
    f = Function(V)
    #randomly construct an f uniformly accorss all possible values
    numCords = len(f.dat.data)
    lowBound = np.finfo(dtype="float32").min
    upBound  = np.finfo(dtype="float32").max
    norm = 10e25
    data = np.random.uniform(low=lowBound/norm,high=upBound/norm,size=numCords)
    f = Function(V,val=data)


    preZipPoints = []
    for b in bounds:
        x = np.random.uniform(low=b[0]/norm,high=b[1]/norm,size=npoints)
        preZipPoints.append(x)

    
    
    zipPoints = np.array(preZipPoints).T

    #write the diderot file
    #prepare evals and print statements
    evals = []
    printStms = []
    for x in range(0,npoints):
        z = zipPoints[x]
        printStms.append("\tprint(out{0},\"\\n\");\n".format(x))
        if dim == 2:
            evals.append("\tvec2 pos{0} = [{1},{2}];tensor[] out{0} = inst(F,pos{0});\n".format(x,z[0],z[1]))

        elif dim ==3:
            evals.append("\tvec3 pos{0} = [{1},{2},{3}];\n".format(x,z[0],z[1],z[2]))
            
            
            
    didFile = """
    input int imgRes = 10;
    input fem#1(2)[] f;
    fnspace V = FunctionSpace(%(mesh)s(2,2), %(elem)s(), %(d)s);
    string path = "../../fnspace_data/";
    ofield#1(2)[] F = convert(f, V, path);
    strand sample(int ui, int vi) {
    output tensor[] out = 0;
    %(ev)s



    update {
    %(ps)s
    
    stabilize;
    }
    }

    initially [ sample(ui, vi) | vi in 0..(0), ui in 0..(0) ];
    """% {"mesh" : meshname, "elem" : element, "d" : str(dim), "ev" : "".join(evals), "ps" : "".join(printStms) }

    with open("test/mesh_d2s_single.diderot",'w') as fi:
        fi.write(didFile)

    #Compile this -> hope it works
    os.system("cd test; ./run.sh")

    #run this and collect the output
    #steal from https://stackoverflow.com/questions/9488560/capturing-print-output-from-shared-library-called-from-python-with-ctypes-module
    # the pipe would fail for some reason if I didn't write to stdout at some point
    # so I write a space, then backspace (will show as empty in a normal terminal)
    sys.stdout.write(' \b')
    pipe_out, pipe_in = os.pipe()
    # save a copy of stdout
    stdout = os.dup(1)
    # replace stdout with our write pipe
    os.dup2(pipe_in, 1)

    # check if we have more to read from the pipe
    def more_data():
        r, _, _ = select.select([pipe_out], [], [], 0)
        return bool(r)

    # read the whole pipe
    def read_pipe():
        out = ''
        while more_data():
                out += os.read(pipe_out, 1024)

        return out
    #run
    single_mesh("../data/out.nrrd",f,10,"test/mesh_d2s_single_init.so")
    #os.dup2(stdout, myStdOut)
    os.dup2(stdout, 1)
    print read_pipe()

    
    
run_test(UnitSquareMesh(2,2),"UnitSquareMesh","Lagrange",2,[(0,1),(0,1)],2,10)


