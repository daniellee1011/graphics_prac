// Files that end in the .cpp extension are 'C++' files

// Bring in libraries here
#include <iostream>  // input and output 'stream' library
#include <vector>    // std::vector data structure.

void PrintVector(const std::vector<int> &v) {
  std::cout << "PrintVecot" << std::endl;
  for (int i = 0; i < v.size(); i++) {
    std::cout << v.at(i) << std::endl;
  }
}

void PrintRawArray(int array[], int size) {
  std::cout << "PrintRawArray" << std::endl;
  for (int i = 0; i < size; i++) {
    std::cout << array[i] << std::endl;
  }
}

int main() {
  // Source code here
  std::cout << "hello my name is Dongwook" << std::endl;

  // Raw array
  int array[3] = {1, 2, 3};

  // This is a data structure, that abstracts around
  // a raw array, so it's a little safer, and can
  // havef some member functions do actions.
  std::vector<int> myVector;
  myVector.push_back(1);
  myVector.push_back(2);
  myVector.push_back(3);

  // std::cout << "myVector[0]: " << myVector[0] << std::endl;
  // std::cout << "myVector[0]: " << myVector[1] << std::endl;
  // std::cout << "myVector[0]: " << myVector[2] << std::endl;

  // for (int i = 0; i < myVector.size(); i++)
  // {
  //     std::cout << myVector[i] << std::endl;
  // }

  // for (auto &e : myVector)
  // {
  //     std::cout << e << std::endl;
  // }

  PrintVector(myVector);
  PrintRawArray(myVector.data(), myVector.size());

  return 0;
}