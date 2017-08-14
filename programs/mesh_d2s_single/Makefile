# Makefile for mesh_d2s_single viewer demo
#
# This code is part of the Diderot Project (http://diderot-language.cs.uchicago.edu)
#
# COPYRIGHT (c) 2015 The University of Chicago
# All rights reserved.
#

SHELL =		/bin/sh

CC =		clang
CPPFLAGS =	-I../util -I/opt/local -I/usr/local/  -I/home/teodoro/gitcode/again/femprime/src/lib/include -I.
CFLAGS =	-O3 -fPIC -g
FRAMEWORKS =	-framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo
LDFLAGS =	-L/opt/local/lib -L/usr/local/lib -L/usr/local/ -lteem  -lpng $(FRAMEWORKS) -dynamiclib

DIDEROTC =		/home/teodoro/gitcode/again/femprime/bin/diderotc 
DIDEROTC_FLAGS =	--namespace=mesh_d2s_single --target=pthread --debug

UTIL_SRCS =		../../util/util.c



# mesh_d2s_single_init.so: mesh_d2s_single_init.a
# 	$(CC) -g -shared -o mesh_d2s_single_init.so mesh_d2s_single_init.a -Wl,--whole-archive -L.  -Wl,--no-whole-archive

# mesh_d2s_single_init.a: mesh_d2s_single_init.o
# 	ar -rv mesh_d2s_single_init.a mesh_d2s_single_init.o

# mesh_d2s_single_init.o: mesh_d2s_single.o mesh_d2s_single_init.c

mesh_d2s_single.o:	mesh_d2s_single.diderot
	$(DIDEROTC) $(DIDEROTC_FLAGS)  --namespace=mesh_d2s_single  mesh_d2s_single.diderot

clean:
	rm -rf libmesh_d2s_single.dylib mesh_d2s_single.o  mesh_d2s_single_init.o mesh_d2s_single.log mesh_d2s_single_init.so mesh_d2s_single_init.a 

dist-clean:	clean
	rm -f Makefile
