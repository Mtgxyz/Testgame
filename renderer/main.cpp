#include <renderer/main.h>
#include <iostream>
#include <GL/glew.h>
using namespace std;
MainClass::MainClass(int width, int height)
{
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Testgame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);
}
void MainClass::start()
{
  /* Extension wrangler initialising */
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << endl;
    throw nullptr;
  }
  if(!init()) {
    cerr << "Error: could not init game!" << endl;
    throw nullptr;
  }
  while(tick());
  stop();
}
MainClass::~MainClass()
{
  SDL_DestroyWindow(window);
  SDL_Quit();
}
