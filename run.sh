cd programs
cd mesh_step
sh run.sh
cd ..
cd mesh_d2s_single
sh run.sh
cd ..
cd ..
py.test -v sample.py