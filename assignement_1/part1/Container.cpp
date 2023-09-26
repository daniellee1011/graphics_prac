#include "Container.hpp"

#include <iostream>

// Constructor
Container::Container(std::string name) {
  m_name = name;
  std::cout << name << " Constructred" << std::endl;
}

// Destructor
Container::~Container() { std::cout << m_name << " Destroyed" << std::endl; }

void Container::AddData(int i) { m_vector.push_back(i); }

void Container::PrintData() {
  for (int i = 0; i < m_vector.size(); i++) {
    std::cout << m_vector[i] << std::endl;
  }
}