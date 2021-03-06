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
import time 
cwd = abspath(dirname(__file__))

sys.path.insert(0, '../../lib/')
from connect import *


def run_test(mesh,meshname,element,dim,bounds, degree,res,stepsize,f,num):
    r = random.uniform(0,1)
    dirname = "test"+str(r)
    print("The dirname is {0}".format(dirname))
    os.system("cp -R test "+dirname)
    time.sleep(5)
    ps = ",".join(map(lambda x: "int u"+str(x),range(dim)))
    evals = "[" + ",".join(map(lambda x: "u"+str(x),range(dim))) + "]"
    pss = ",".join(map(lambda x: "u{0} in 0..(imgRes-1)".format(x),range(dim)))
    ess = evals[1:-1]
    didFile = """
    input int imgRes = %(res)s;
    input fem#1(2)[] f;
    input real stepSize = %(step)s;
    fnspace V = FunctionSpace(%(mesh)s, %(elem)s(), %(d)s);
    string path = "../../../fnspace_data/";
    ofield#1(2)[] F = convert(f, V, path);
    strand sample(%(es)s) {
    
    vec%(dim)s pos = %(ev)s *stepSize;
    output tensor[] out = inst(F,pos);




    update {
    stabilize;
          }
    }

    initially [ sample(%(ess)s) | %(pss)s ];
    """% {"mesh" : meshname, "elem" : element, "d" : str(degree), "es" : ps, "ev" : evals, "pss" : pss, "ess" : ess, "res" : res, "step" : stepsize, "dim" : dim }

    try:
        with open(dirname+"/mesh_d2s_single.diderot",'w+') as fi:
            fi.write(didFile)
    except:
        os.system("rm -rf test0.*")
        dirname = "temp"
        a = os.getcwd()
        cmd = "cp -R " + a + "/test "+ a +"/" + dirname
        dirname = a +"/" + dirname
        print(cmd)
        os.system(cmd)
        time.sleep(5)
        os.system("ls "+ dirname)
        with open(dirname+"/mesh_d2s_single.diderot",'w+') as fi:
            fi.write(didFile)

    


    #Compile this -> hope it works
    os.system("cd "+ dirname +"; ./run.sh")
    
    #run
    print("Running test {0}".format(num))
    
    total = single_mesh_step("out.nrrd",f,res,stepsize,dirname+"/mesh_d2s_single_init.so")

    #os.dup2(stdout, myStdOut)
    
    return(total)
    
    



lowBound = -10.0 #np.finfo(dtype="float32").min
upBound  = 10.0 #np.finfo(dtype="float32").max
norm = 1.0
data = np.ones((1000000,),dtype="float32") #a possible breakage point
data2 = []

for r in range(1,64+1):
    mesh = UnitSquareMesh(r,r)
    nc = len(mesh.coordinates.cell_node_map().values)
    meshName = "UnitSquareMesh({0},{0})".format(r)
    element = "Lagrange"
    bounds = [(0,1),(0,1)]
    degree = 5
    V = FunctionSpace(mesh,"Lagrange",degree=degree)
    f = Function(V)

    #randomly construct an f uniformly accorss all possible values
    numCords = len(f.dat.data)
    f = Function(V,val=data[0:numCords])
    res = 1000
    start = time.clock()
    run_test(mesh,meshName,element,2,bounds,degree,res,1.0/float(res),f,r)
    end = time.clock()
    total = end-start
    data2.append((nc,total))
    print(data2)
                         #mesh,meshname,element,dim,bounds, degree,npoints

for x in data2:
    print("{0},{1}".format(x[0],x[1]))



