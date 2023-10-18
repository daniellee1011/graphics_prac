#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[], char *env[]) {
  std::cout << std::endl;
  std::cout << "argc: " << argc << std::endl;

  if (argc < 2) {
    std::cout << "Usage: ./argc some_string" << std::endl;
    return 0;
  }

  for (int i = 0; i < argc; i++) {
    std::cout << "[" << i << "]" << argv[i] << std::endl;
  }

  std::cout << std::getenv("PATH") << std::endl;

  std::cout << "\nenv: " << env << std::endl;
  std::cout << "\nenv: " << *env << std::endl;
  int i = 0;
  for (;;) {
    std::cout << env[i++];
    if (env[i] == nullptr) {
      break;
    }
    break;
  }

  std::cout << std::endl;

  return 0;
}