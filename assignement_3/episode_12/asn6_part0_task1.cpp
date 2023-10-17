// This is a 'toy' example of using the std::vector
// Compile with:
// g++ -std=c++20 vector.cpp -o prog
// Run with:
// ./prog

#include <iostream>
#include <vector> // Our new library

// Here is a struct that holds
// the indices that make up a triangle.
// Note that we are using a 'struct' as a
// 'Plain-old datatype' or POD, to hold
// some information. No fancy constructors or
// destructors needed since we are only
// storing primitive data (i.e., ints, floats, char, etc.)
// types in each field.
struct Triangle {
  unsigned int i1, i2, i3;
};

// Here is a std::vector that holds all of the indices.
// Since we are creating it outside of our main,
// it is a global variable (i.e., it is availablle everywhere).
// NOTE: This is a toy example--but I want you to pay attention
// 	 that this is allocated in some globally accessible form of memory.
// 	 Generally we do not like global variables.
std::vector<unsigned int> indiciesList;

// Entry function into our C++ program.
int main() {

  // This local variable triangleList holds all of the triangles
  // for our model. We are allocating it on the stack here.
  // Remember, things allocated on the stack are 'deleted'
  // when we exit the function from which they were allocated
  // (in this case, the main() function).
  std::vector<Triangle> triangleList;

  // We create a first triangle. It will be made up of
  // whatever 'vertex' 0, 1, and 2 are.
  Triangle t;
  t.i1 = 0;
  t.i2 = 1;
  t.i3 = 2;

  // Here is a second triangle. This time it is made up
  // of wherever triangle 2, 1, and 3 are.
  Triangle t1;
  t1.i1 = 2;
  t1.i2 = 1;
  t1.i3 = 3;

  // And a third triangle...
  Triangle t2;
  t2.i1 = 2;
  t2.i2 = 1;
  t2.i3 = 3;

  // We now 'append' each of our triangles to our triangle list.
  triangleList.push_back(t);
  triangleList.push_back(t1);
  triangleList.push_back(t2);

  // We can print out some information about each of our vectors.
  // This tells us how many triangles we have.
  std::cout << "triangleList.size():" << triangleList.size() << "\n";

  // Here is another example.
  // Careful, this tells us the size of a data type.
  // Do you understand what triangList.data() is giving us access to? Look it
  // up!
  std::cout << "sizeof(triangleList.data()):" << sizeof(triangleList.data())
            << "\n";
  // Here we print out the size of each 'data type' NOT how much data we have
  // stored within them.
  std::cout << "sizeof(triangleList):" << sizeof(triangleList) << "\n";
  std::cout << "sizeof(Triangle):" << sizeof(Triangle) << "\n";

  // Here is an array with 12 elements, each element that is 4 bytes.
  // I am also allocating it on the stack, which costs me 48 bytes.
  unsigned int indices[] = {0, 1, 2, 0, 3, 4, 7, 8, 9, 10, 11, 12};

  // Let's also add to our 'global indiciesList' some things.
  // Remember, indiciesList is on the heap.
  indiciesList.push_back(0);
  indiciesList.push_back(1);
  indiciesList.push_back(2);
  indiciesList.push_back(0);
  indiciesList.push_back(3);

  // Arrays allocated on the stack will tell me exactly how big the structure
  // is. That is because the sizeof operator has the exact information needed
  // available to compute the size when a data structure is in local scope
  // (i.e., stack allocated)
  std::cout << "sizeof(indices) on stack:" << sizeof(indices) << "\n";

  // sizeof here only tells me the size of a 'std::vector' type. Be careful--so
  // this means that anything you declare global, or otherwise declare on the
  // *heap* (i.e., using 'new') will not work properly with the sizeof operator.
  std::cout << "sizeof(indiciesList)     :" << sizeof(indiciesList) << "\n";

  return 0;
}