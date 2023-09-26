// Compile with:
// g++ -std=c++17 output.cpp -o prog
#include <fstream>
#include <iostream>

int main() {

  // I hope you are typing out the examples and experimenting.

  std::ofstream outFile;

  outFile.open("temp.txt");

  outFile << "# Some image data" << std::endl;
  outFile << "P3" << std::endl;

  outFile.close();

  return 0;
}