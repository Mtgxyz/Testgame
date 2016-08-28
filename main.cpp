#include <iostream>
#include <cstdlib>
#include <main.h>
#include <SDL.h>
#include <GL/glew.h>
#include <renderer/shader.h>
using namespace std;
bool TestGame::init()
{
  GLint link_ok = GL_FALSE;
  //Compile Vertex shader
  vs = new VertexShader("shaders/triangle.v.glsl");
  if(!vs->compile()) {
    throw nullptr;
  }
  //Compile Fragment shader
  fs = new FragmentShader("shaders/triangle.f.glsl");
  if(!fs->compile()) {
    throw nullptr;
  }
  //Linking
  vector<Shader *> shaders;
  shaders.push_back(vs);
  shaders.push_back(fs);
  program=link(shaders);
  //Set attributes
  const char* attribute_name = "coord2d";
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (attribute_coord2d == -1) {
    cerr << "Could not bind attribute " << attribute_name << endl;
    throw nullptr;
  }
  
  return true;
}
void TestGame::stop()
{
  //To be written
}
bool TestGame::tick()
{
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT)
      return false;
    }
  render();
  return true;
}
void TestGame::render()
{
  //Clear Background
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glUseProgram(program);
  glEnableVertexAttribArray(attribute_coord2d);

  
  t1.render(attribute_coord2d);
  t2.render(attribute_coord2d);
  t3.render(attribute_coord2d);

  glDisableVertexAttribArray(attribute_coord2d);

  // Display the result
  SDL_GL_SwapWindow(window);
}
TestGame::~TestGame()
{
  glDeleteProgram(program);
  delete fs;
  delete vs;
}

int main(int argc, char **argv) {
  TestGame game;
  game.start();
  return 0;
}
