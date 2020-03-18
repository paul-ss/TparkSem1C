#!/bin/bash

BUILD_DIR=build_stress
LOG_FILE_NAME=log.txt
export COVERAGE=0

mkdir ${BUILD_DIR}
cd ${BUILD_DIR}


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





echo "Naive method" > ${LOG_FILE_NAME}
echo "===================" >> ${LOG_FILE_NAME}

echo "solve matrix 100x100..."
./hw2_naive 10.txt >> ${LOG_FILE_NAME}

echo "solve matrix 1000x1000..."
./hw2_naive 1.txt >> ${LOG_FILE_NAME}

echo "solve matrix 5000x5000..."
./hw2_naive 2.txt >> ${LOG_FILE_NAME}

echo "solve matrix 10000x10000..."
./hw2_naive 3.txt >> ${LOG_FILE_NAME}





echo "Optimised method" >> ${LOG_FILE_NAME}
echo "===================" >> ${LOG_FILE_NAME}

echo "solve matrix 100x100..."
./hw2_opt 10.txt >> ${LOG_FILE_NAME}

echo "solve matrix 1000x1000..."
./hw2_opt 1.txt >> ${LOG_FILE_NAME}

echo "solve matrix 5000x5000..."
./hw2_opt 2.txt >> ${LOG_FILE_NAME}

echo "solve matrix 10000x10000..."
./hw2_opt 3.txt >> ${LOG_FILE_NAME}



cat ${LOG_FILE_NAME}

cd ..
rm -r ${BUILD_DIR}

