#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    std::cout << "fail" << std::endl;
    return 1;
  } else {
    std::cout << "success" << std::endl;
    SDL_Log("SDL initialized successfully!");
  }

  SDL_Quit();
  return 0;
}