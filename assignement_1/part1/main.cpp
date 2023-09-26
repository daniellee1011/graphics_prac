#include <iostream>  // I/O stream
#include <string>
#include <vector>

#include "Container.hpp"

int main() {
  int i = 7;
  float f = 3.14;
  Container myContainer("myContainer");
  //   myContainer.m_vector.push_back(1);
  myContainer.AddData(1);
  myContainer.AddData(2);
  myContainer.AddData(3);
  myContainer.PrintData();

  Container myContainer2("myContainer2");
  myContainer2.AddData(-1);
  myContainer2.AddData(-2);
  myContainer2.AddData(-3);
  myContainer2.PrintData();

  return 0;
}