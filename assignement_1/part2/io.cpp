// Compile with:
// g++ -std=c++17 io.cpp -o prog
#include <iostream>

int main() {

  // Type out the example and have some fun with this one.

  std::cout << "Hello" << std::endl;
  std::cout << "How old are you?" << std::endl;

  int age;

  std::cin >> age;

  std::cout << "That is great you are " << age << std::endl;

  return 0;
}