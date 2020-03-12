//
// Created by paul_s on 09.03.2020.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

#define DEFAULT_SIZE 30

void generateMatrix(std::ostream &, int, int);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Invalid input arguments" << std::endl;
    return 0;
  }
  std::ofstream os(argv[1]);

  int rows = DEFAULT_SIZE;
  int cols = DEFAULT_SIZE;
  if (argc >= 4) {
    std::stringstream rowsStream(argv[2]);
    std::stringstream colsStream(argv[3]);
    rowsStream >> rows;
    colsStream >> cols;
  }

  generateMatrix(os, rows, cols);
}


void generateMatrix(std::ostream &os, int rows, int cols) {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  os << rows << " " << cols << std::endl;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      os << (double) ((int) mersenne()) / 1000000.0 << " ";
    }
    os << std::endl;
  }
}