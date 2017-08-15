import sys
from os.path import abspath, dirname
import pytest
import os
from os import path
cwd = abspath(dirname(__file__))
from makejson import makejson
from init import *


#path to data output
imgpath='data/'


#old way, use with fem branch
def cut_old(name, f, V,res, stepSize):
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    vis_diderot.basic_d2s_sample(namenrrd, f, res, res, stepSize, 1)
    #visualize result
    quantize(namenrrd,namepng)
    os.system('open ' + namepng)
    #namepvd=datafile +'.pvd'
    #File(namepvd) << f

#make json file now
def cut_json(name, f, V, res, stepSize):
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    namedata = datafile +'.json'#namedata: name of the output json file
    
    # first cut
    makejson(V, namedata)
    os.system('sh compileDiderot.sh') # compiles diderot program
    # name data needs to be name of nameing in diderot program
    data_d2s(namenrrd, f, res, res, stepSize)
    #visualize result
    quantize(namenrrd,namepng)
    os.system('open ' + namepng)


#relies on previously created json file
def cut_new(name, f, res):
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    mesh_d2s_single(name, f, res)
    #visualize result
    quantize(namenrrd,namepng)
    os.system('open ' + namepng)



#relies on previously created json file
def cut_newTwo(name, f, g, res):
    datafile = imgpath+name
    namepng = datafile +'.png'
    namenrrd = datafile +'.nrrd'
    # mesh data
    mesh_d2s_twofields(name, f, g, res)
    #visualize result
    quantize(namenrrd,namepng)
    os.system('open ' + namepng)
