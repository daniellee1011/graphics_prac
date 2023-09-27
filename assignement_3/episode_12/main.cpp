// Compile command:
// g++ .\main.cpp -o prog -lmingw32 -lSDL2main -lSDL2
// g++ .\main.cpp .\src\glad.c -I.\include\ -o prog -lmingw32 -lSDL2main -lSDL2

// Third Party Libraries
#include <SDL2/SDL.h>
#include <glad/glad.h>

// C++ Standard Template Library
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Globals
int gScreenHeight = 640;
int gScreenWidth = 480;
SDL_Window *gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit = false;

// VAO
GLuint gVertexArrayObject = 0;

// VBO
GLuint gVertexBufferObject = 0;

std::string LoadShaderAsString(const std::string &filename) {
  std::string result = "";

  std::string line = "";
  std::ifstream myFile(filename.c_str());

  if (myFile.is_open()) {
    while (std::getline(myFile, line)) {
      result += line + '\n';
    }
    myFile.close();
  }

  return result;
}

// Program Object (for our shader)
GLuint gGraphicsPipelineShaderProgram = 0;

GLuint CompileShader(GLuint type, const std::string &source) {
  GLuint shaderObject;

  if (type == GL_VERTEX_SHADER) {
    shaderObject = glCreateShader(GL_VERTEX_SHADER);
  } else if (type == GL_FRAGMENT_SHADER) {
    shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
  }

  const char *src = source.c_str();
  glShaderSource(shaderObject, 1, &src, nullptr);
  glCompileShader(shaderObject);

  return shaderObject;
}

GLuint CreateShaderProgram(const std::string &vertexshadersource,
                           const std::string &fragmentshadersource) {
  GLuint programObject = glCreateProgram();

  GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexshadersource);
  GLuint myFragmentShader =
      CompileShader(GL_FRAGMENT_SHADER, fragmentshadersource);

  glAttachShader(programObject, myVertexShader);
  glAttachShader(programObject, myFragmentShader);
  glLinkProgram(programObject);

  // Validate our program
  glValidateProgram(programObject);
  // glDetachShader, glDeleteShader

  return programObject;
}

void CreateGraphicsPipeline() {
  std::string vertexShaderSource = LoadShaderAsString(".\\shaders\\vert.glsl");
  std::string fragmentShaderSource =
      LoadShaderAsString(".\\shaders\\frag.glsl");

  gGraphicsPipelineShaderProgram =
      CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void GetOpenGLVersionInfo() {
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
}

void VertexSpecification() {

  // Lives on the CPU
  const std::vector<GLfloat> vertexPosition{
      // x y z
      -0.8f, -0.8f, 0.0f, // vertex 1
      0.8f,  -0.8f, 0.0f, // vertex 2
      0.0f,  0.8f,  0.0f  // vertex 3
  };

  // We start setting things up on the GPU
  glGenVertexArrays(1, &gVertexArrayObject);
  glBindVertexArray(gVertexArrayObject);

  // Start generating our VBO
  glGenBuffers(1, &gVertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, vertexPosition.size() * sizeof(GLfloat),
               vertexPosition.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
}

void InitializeProgram() {
  std::cout << "InitializeProgram function starts" << std::endl;

  std::cout << "SDL_Init before" << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL2 could not initialize video subsystem" << std::endl;
    exit(1);
  }

  std::cout << "SDL_GL_SetAttribute before" << std::endl;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  std::cout << "SDL_CreateWindow before" << std::endl;
  gGraphicsApplicationWindow = SDL_CreateWindow(
      "OpenGL Window", 0, 0, gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL);

  if (gGraphicsApplicationWindow == nullptr) {
    std::cout << "SDL_Window was not able to be created" << std::endl;
    exit(1);
  }

  std::cout << "SDL_GL_CreateContext before" << std::endl;
  gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);
  if (gOpenGLContext == nullptr) {
    std::cout << "OpenGL Context was not able to be created" << std::endl;
    exit(1);
  }

  // initiailize the Glad Libarary
  std::cout << "gladLoadGLLoader before" << std::endl;
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    std::cout << "glad was not initialized" << std::endl;
    exit(1);
  }

  GetOpenGLVersionInfo();
}

void Input() {
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      std::cout << "Goodbye!" << std::endl;
      gQuit = true;
    }
  }
}

void PreDraw() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glViewport(0, 0, gScreenWidth, gScreenHeight);
  glClearColor(1.f, 1.f, 0.f, 1.f);

  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glUseProgram(gGraphicsPipelineShaderProgram);
}

void Draw() {
  glBindVertexArray(gVertexArrayObject);
  glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MainLoop() {
  while (!gQuit) {
    Input();

    PreDraw();

    Draw();

    SDL_GL_SwapWindow(gGraphicsApplicationWindow);
  }
}

void CleanUp() {
  SDL_DestroyWindow(gGraphicsApplicationWindow);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  std::cout << "main function starts" << std::endl;

  InitializeProgram();

  VertexSpecification();

  CreateGraphicsPipeline();

  MainLoop();

  CleanUp();

  return 0;
}