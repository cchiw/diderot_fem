make clean
make
make mesh_d2s_single_init.o
clang++ -m64 -std=gnu++11 -shared -pthread -mavx2 -msse4.2 -I/home/teodoro/gitcode/again/femprime/src/lib/include   -I/home/teodoro/gitcode/again/teem/teem-src/teem-build/include -o mesh_d2s_single_init.so mesh_d2s_single_init.o mesh_d2s_single.o -lteem -lpng
#g++ -shared -I/home/teodoro/gitcode/again/femprime/src/lib/include  -o mesh_d2s_single_init.so mesh_d2s_single_init.o mesh_d2s_single.o -lteem -lpng
#g++  -O3 -fPIC -shared -I../util -I/opt/local -I/usr/local/  -I/home/teodoro/gitcode/again/femprime/src/lib/include   -o mesh_d2s_single_init.so mesh_d2s_single_init.c mesh_d2s_single.o  -Wl,--whole-archive -lteem -Wl,--no-whole-archive
