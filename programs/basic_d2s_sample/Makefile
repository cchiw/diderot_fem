# Makefile for basic_d2s_sample viewer demo
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

DIDEROTC =		/Users/chariseechiw/diderot/fem/bin/diderotc 
DIDEROTC_FLAGS =	--namespace=basic_d2s_sample --target=pthread

UTIL_SRCS =		../../util/util.c



basic_d2s_sample.o:	basic_d2s_sample.diderot
	$(DIDEROTC) $(DIDEROTC_FLAGS)  --namespace=basic_d2s_sample  basic_d2s_sample.diderot

clean:
	rm -rf libbasic_d2s_sample.dylib basic_d2s_sample.o  basic_d2s_sample.h

dist-clean:	clean
	rm -f Makefile
