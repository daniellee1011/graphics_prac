#include "OBJModel.hpp"
// Third Party Libraries
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

// C++ Standard Template Library (STL)
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

SDL_Window *window = nullptr;
SDL_GLContext glContext;

const char *vertexShaderSource = R"glsl(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

)glsl";

const char *fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Simple orange color
}
)glsl";

GLuint CompileShader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);
  // Check for compile errors here...
  return shader;
}

void Initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError()
              << std::endl;
    exit(1);
  }

  // Setup the OpenGL Context
  // Use OpenGL 4.1 core or greater
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  // We want to request a double buffer for smooth updating.
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  window = SDL_CreateWindow("OpenGL OBJ Loader", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_OPENGL);
  if (!window) {
    std::cerr << "Window could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    exit(1);
  }

  glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    std::cerr << "OpenGL context could not be created! SDL Error: "
              << SDL_GetError() << std::endl;
    exit(1);
  }

  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    std::cerr << "Failed to initialize GLAD!" << std::endl;
    exit(1);
  }

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CleanUp() {
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  Initialize();

  //   OBJModel
  //   model("C:\\Users\\kauvo\\Desktop\\23_fall\\cs_5310_cg\\graphics_"
  //                  "prac\\common\\objects\\cube.obj");
  OBJModel model("C:\\Users\\kauvo\\Desktop\\23_fall\\cs_5310_cg\\graphics_"
                 "prac\\common\\objects\\bunny_centered.obj");

  // TODO: Create a shader program using vertexShaderSource and
  // fragmentShaderSource. Compile, link, and use the shader program when
  // rendering the model.

  GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "Vertex Shader compilation failed\n" << infoLog << std::endl;
  }

  GLuint fragmentShader =
      CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "Fragment Shader compilation failed\n" << infoLog << std::endl;
  }

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "Shader Program linking failed\n" << infoLog << std::endl;
  }

  // Check for linking errors here...

  glUseProgram(shaderProgram);

  // Get uniform locations
  GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
  GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

  // Set up the static matrices
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  //   modelMatrix =
  //       glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f)); // Scale by
  //       half

  glm::mat4 viewMatrix =
      glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), // camera position
                  glm::vec3(0.0f, 0.0f, 0.0f), // target position
                  glm::vec3(0.0f, 1.0f, 0.0f)  // up vector
      );
  glm::mat4 projection = glm::perspective(
      glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f,
      100.0f);

  GLint viewLoc = glGetUniformLocation(shaderProgram, "view");

  bool isRunning = true;
  SDL_Event e;

  while (isRunning) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Set the uniform values for the active shader
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    model.render(); // This should render the OBJ model

    SDL_GL_SwapWindow(window);
  }

  CleanUp();
  return 0;
}