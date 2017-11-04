make observ.o
make observ_init.o
make observ_init.so
python observ.py
# ./dvr -camEye 10 20 5 -camAt 0 0 0 -camUp 0 0 1 -camNear -2 -camFar 2 -camFOV 8 -iresU 400 -iresV 400 -thick 0.1 -refStep 0.1 -rayStep 0.01 -isoval 0.0 -cmin -1 -cmax 1
overrgb -i rgba.nrrd -b 1 1 1 -g 1.2 -o cat.png
open cat.png