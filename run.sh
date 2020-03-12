#!/bin/bash

mkdir build
cd build
cmake ..
make

echo "generate matrix 1000x1000..."
./gen 1.txt 1000 1000

echo "generate matrix 5000x5000..."
./gen 2.txt 5000 5000

echo "solve matrix 1000x1000..."
./hw-2 1.txt > ../log1.txt

echo "solve matrix 5000x5000..."
./hw-2 2.txt > ../log2.txt

cd ..
rm -r build

