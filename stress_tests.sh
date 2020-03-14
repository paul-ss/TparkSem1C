#!/bin/bash

mkdir build
cd build
export COVERAGE=0
cmake ..
make 

echo "generate matrix 100x100..."
./gen 10.txt 100 100

echo "generate matrix 1000x1000..."
./gen 1.txt 1000 1000

echo "generate matrix 5000x5000..."
./gen 2.txt 5000 5000

echo "generate matrix 10000x10000..."
./gen 3.txt 10000 10000





echo "Naive method" > ../log.txt
echo "===================" >> ../log.txt

echo "solve matrix 100x100..."
./hw2_naive 10.txt >> ../log.txt

echo "solve matrix 1000x1000..."
./hw2_naive 1.txt >> ../log.txt

echo "solve matrix 5000x5000..."
./hw2_naive 2.txt >> ../log.txt

echo "solve matrix 10000x10000..."
./hw2_naive 3.txt >> ../log.txt





echo "Optimised method" >> ../log.txt
echo "===================" >> ../log.txt

echo "solve matrix 100x100..."
./hw2_opt 10.txt >> ../log.txt

echo "solve matrix 1000x1000..."
./hw2_opt 1.txt >> ../log.txt

echo "solve matrix 5000x5000..."
./hw2_opt 2.txt >> ../log.txt

echo "solve matrix 10000x10000..."
./hw2_opt 3.txt >> ../log.txt



cat ../log.txt

cd ..
rm -r build

