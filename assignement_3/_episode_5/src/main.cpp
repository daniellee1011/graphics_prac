#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

// Globals
int gScreenHeight = 640;
int gScreenWidth = 480;
SDL_Window *gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit = false; // If ture, we quit

void GetOpenGLVersionInfo() {
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
}

void InitializeProgram() {
  std::cout << "About to initialize SDL..." << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL2 could not initialize video subsystem" << std::endl;
    exit(1);
  }
  std::cout << "SDL initialized." << std::endl;

  GLenum err = glGetError();
  while (err != GL_NO_ERROR) {
    std::cout << "OpenGL error: " << err << std::endl;
    err = glGetError();
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  std::cout << "SDL attributes set." << std::endl;

  gGraphicsApplicationWindow =
      SDL_CreateWindow("OpenGL Window",    /* Title of the SDL window */
                       0,                  /* Position x of the window */
                       0,                  /* Position y of the window */
                       gScreenWidth,       /* Width of the window in pixels */
                       gScreenHeight,      /* Height of the window in pixels */
                       SDL_WINDOW_OPENGL); /* Additional flag(s) */

  if (gGraphicsApplicationWindow == nullptr) {
    std::cout << "SDL_Window was not able to be created" << std::endl;
    exit(1);
  }
  std::cout << "SDL window created." << std::endl;

  gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

  if (gOpenGLContext == nullptr) {
    std::cout << "OpenGL context not available\n";
    exit(1);
  }
  std::cout << "OpenGL context created." << std::endl;

  //   initialize the Glad Library
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    std::cout << "glad was not initialized" << std::endl;
    exit(1);
  }
  std::cout << "GLAD initialized." << std::endl;

  //   GetOpenGLVersionInfo();
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

void PreDraw() {}

void Draw() {}

void MainLoop() {
  while (!gQuit) {
    Input();

    PreDraw();

    Draw();

    // Update the screen
    SDL_GL_SwapWindow(gGraphicsApplicationWindow);
  }
}

void CleanUp() {
  SDL_DestroyWindow(gGraphicsApplicationWindow);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  std::cout << "Starting program..." << std::endl;

  InitializeProgram();

  MainLoop();

  CleanUp();

  return 0;
}