make clean
make ex2.o
make ex2_init.o
make ex2_init.so
py.test -v ex2.py
rm *.o
rm *.so
rm *.h
rm *.log