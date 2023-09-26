// Compile with:
// g++ -std=c++17 datasize.cpp -o prog
#include <cstdint>
#include <iostream>

int main() {

  // Type out the example.
  // Actually type it out--that is how you will learn and
  // build your muscle memory with the language.
  // Do not copy & paste...actually type it out.
  // Change some values, play around, experiment.

  std::cout << "Data size of int in bytes = " << sizeof(int) << std::endl;

  std::cout << "Data size of char in bytes = " << sizeof(char) << std::endl;

  std::cout << "Data size of uint8_t in bytes = " << sizeof(uint8_t)
            << std::endl;

  std::cout << "Data size of float in bytes = " << sizeof(float) << std::endl;

  std::cout << "Data size of double in bytes = " << sizeof(double) << std::endl;

  return 0;
}