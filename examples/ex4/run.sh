rm data.json
rm *.*o
rm *.log
rm *.h

py.test -v ex4.py
rm ../data/*.nrrd