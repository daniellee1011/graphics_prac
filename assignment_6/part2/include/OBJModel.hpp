#ifndef OBJMODEL_HPP
#define OBJMODEL_HPP

// Third Party Libraries
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

// C++ Standard Template Library (STL)
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class OBJModel {
public:
  OBJModel(const std::string &filepath);
  ~OBJModel();

  void render() const;

private:
  struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
  };

  std::vector<Vertex> vertices;
  unsigned int vao, vbo;
  void setupBuffers();
};

#endif // OBJMODEL_HPP
