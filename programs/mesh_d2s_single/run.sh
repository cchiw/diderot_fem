make clean
make
g++  -O3 -fPIC -shared -I../util -I/opt/local -I/usr/local/  -I/home/teodoro/gitcode/again/femprime/src/lib/include   -o mesh_d2s_single_init.so mesh_d2s_single_init.c mesh_d2s_single.o  -Wl,--whole-archive -lteem -Wl,--no-whole-archive
