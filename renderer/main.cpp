#include <renderer/main.h>
#include <iostream>
#include <GL/glew.h>
using namespace std;
MainClass::MainClass(int width, int height)
{
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Testgame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if(!window) {
    cerr << "Error: can't create window: " << SDL_GetError() << endl;
    throw nullptr;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);
  if(!SDL_GL_CreateContext(window)) {
    cerr << "Error: SDL_GL_CreateContext: " << SDL_GetError() << endl;
    throw nullptr;
  }
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
