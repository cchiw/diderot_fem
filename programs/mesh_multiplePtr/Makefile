# Makefile for mesh_multiplePtr viewer demo
#
# This code is part of the Diderot Project (http://diderot-language.cs.uchicago.edu)
#
# COPYRIGHT (c) 2015 The University of Chicago
# All rights reserved.
#

SHELL =		/bin/sh

CC =		clang
CPPFLAGS =	-I../util -I/opt/local -I/usr/local/ -I/usr/local/ -I/Users/chariseechiw/firedrake/vedat/
CFLAGS =	-O3
FRAMEWORKS =	-framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo
LDFLAGS =	-L/opt/local/lib -L/usr/local/lib -L/usr/local/ -lteem  -lpng $(FRAMEWORKS) -dynamiclib

DIDEROTC =		/Users/chariseechiw/diderot/femprime/bin/diderotc 
DIDEROTC_FLAGS =	--namespace=mesh_multiplePtr --target=pthread

UTIL_SRCS =		../../util/util.c



mesh_multiplePtr.o:	mesh_multiplePtr.diderot
	$(DIDEROTC) $(DIDEROTC_FLAGS)  --namespace=mesh_multiplePtr  mesh_multiplePtr.diderot

clean:
	rm -rf libmesh_multiplePtr.dylib mesh_multiplePtr.o  mesh_multiplePtr.h

dist-clean:	clean
	rm -f Makefile
