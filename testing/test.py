import re
import time
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



def run_test(mesh,meshname,element,dim,bounds, degree,npoints):
    r = random.uniform(0,1)
    dirname = "test"+str(r)
    os.system("cp -R test "+dirname)
    time.sleep(1)
    V = FunctionSpace(mesh,element,degree=degree)
    f = Function(V)
    #randomly construct an f uniformly accorss all possible values
    numCords = len(f.dat.data)
    lowBound = -10.0 #np.finfo(dtype="float32").min
    upBound  = 10.0 #np.finfo(dtype="float32").max
    norm = 1.0
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
            evals.append("\tvec3 pos{0} = [{1},{2},{3}];tensor[] out{0} = inst(F,pos{0});\n".format(x,z[0],z[1],z[2]))
            
            
            
    didFile = """
    input int imgRes = 10;
    input fem#1(2)[] f;
    fnspace V = FunctionSpace(%(mesh)s, %(elem)s(), %(d)s);
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
    """% {"mesh" : meshname, "elem" : element, "d" : str(degree), "ev" : "".join(evals), "ps" : "".join(printStms) }
    os.system("rm test/mesh_d2s_single.diderot; rm test/mesh_d2s_single_init.so; rm test/mesh_d2s_single.cxx; rm test/mesh_d2s_single.o; rm test/mesh_d2s_single_init.o")
    with open(dirname+"/mesh_d2s_single.diderot",'w+') as fi:
        fi.write(didFile)

    


    #Compile this -> hope it works
    os.system("cd "+ dirname +"; ./run.sh")

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
    single_mesh("../data/out.nrrd",f,10,dirname+"/mesh_d2s_single_init.so")
    #os.dup2(stdout, myStdOut)
    os.dup2(stdout, 1)
    didStringResults = read_pipe()
    def g(x):
        print(x)
        u = re.findall(r"[-+]?\d*\.\d+|\d+",x)[0]
        return(float(u))
        # print(x,u)
        # if x[0]=="-":
        #     return(0-float(x[1:]))
        # else:
        #     return(float(x))
        
    didResults =  map(g ,didStringResults.split("\n")[0:-1])
    fResults = map(lambda x: f.at(x),zipPoints)
    errors = []
    for x in range(0,npoints):
        e = abs(didResults[x]-fResults[x])
        if e >= 10e-4: #this is because currently print in diderot only goes to 5sf so this is what we should expect
            errors.append("At test {0}, using values {1} on {3}, the error was {2}".format(x,zipPoints[x],e,(meshname,element,degree)))

    os.system("rm -rf " + dirname)
    if errors==[]:
        print("No errors occured!") #later choose one
        return(errors)
    else:
        print("Error occured")
        return(errors)
    

    


# meshs = [(UnitSquareMesh(2,2),"UnitSquareMesh",[(0,1),(0,1)],2),(UnitSquareMesh(4,2),"UnitSquareMesh",[(0,1),(0,1)],2)]
# elements = ["Lagrange","P"]
# degrees = [1,2,3]

meshs = [(UnitSquareMesh(2,2),"UnitSquareMesh(2,2)",2,[(0,1),(0,1)]),(UnitSquareMesh(3,2),"UnitSquareMesh(3,2)",2,[(0,1),(0,1)]),(UnitCubeMesh(2,2,2),"UnitCubeMesh(2,2,2)",3,[(0,1),(0,1),(0,1)])]
elements = ["Lagrange","P"]
degrees = [2,3]

errors = []

#e = run_test(UnitSquareMesh(2,2),"UnitSquareMesh","P",2,[(0,1),(0,1)],2,10)

#print(e)

for m in meshs:
    for e in elements:
        for d in degrees:
            print(m,e,d)
            t = run_test(m[0],m[1],e,m[2],m[3],d,10)
                         #mesh,meshname,element,dim,bounds, degree,npoints
            errors.append(t)


print(sum(map(len,errors)))
print(errors)

