#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>
#include <vector>

// This is the interface
struct Container {
  Container(std::string name);
  ~Container();
  void AddData(int i);
  void PrintData();

 private:
  std::vector<int> m_vector;
  std::string m_name;
};

#endif