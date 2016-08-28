#include <iostream>
#include <cstdlib>
#include <main.h>
#include <SDL.h>
#include <GL/glew.h>
#include <renderer/shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
  const char* attribute_name = "coord3d";
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (attribute_coord2d == -1) {
    cerr << "Could not bind attribute " << attribute_name << endl;
    throw nullptr;
  }
  attribute_name = "v_color";
  attribute_v_color = glGetAttribLocation(program, attribute_name);
  if (attribute_v_color == -1) {
    cerr << "Could not bind attribute " << attribute_name << endl;
    throw nullptr;
  }
  
  GLfloat triangle_colors[] = {
    1.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 0.0, 0.0,
  };
  const char* uniform_name = "m_transform";
  uniform_m_transform = glGetUniformLocation(program, uniform_name);
  if (uniform_m_transform == -1) {
    cerr << "Could not bind uniform " << uniform_name << endl;
    throw nullptr;
  }
  t1.init(triangle_colors,sizeof(triangle_colors));
  t2.init(triangle_colors,sizeof(triangle_colors));
  t3.init(triangle_colors,sizeof(triangle_colors));
  return true;
}
void TestGame::stop()
{
  //To be written
}
void TestGame::logic()
{
  //Calculate colors
  if(state.bright)
    state.brightness+=0.001;
  else
    state.brightness-=0.001;
  if(state.bright && state.brightness >= 1.0)
    state.bright=false;
  if(!state.bright && state.brightness < 0.0)
    state.bright=true;
  //Apply colors
  GLfloat triangle_colors[] = {
    state.brightness, 0.0, 0.0,
    0.0, state.brightness, 0.0,
    0.0, 0.0, state.brightness,
  };
  float angle = SDL_GetTicks() / 1000.0 * 45;
  glm::vec3 axis_z(0, 0, 1);
  float move = sinf(SDL_GetTicks() / 1000.0 * (2*3.14) / 5);
  glm::mat4 m_transform =  glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_z) * glm::translate(glm::mat4(1.0f), glm::vec3(move, 0.0, 0.0));
  glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
  t1.update(triangle_colors, sizeof(triangle_colors));
  t2.update(triangle_colors, sizeof(triangle_colors));
  t3.update(triangle_colors, sizeof(triangle_colors));
}

bool TestGame::tick()
{
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT)
      return false;
  }
  logic();
  render();
  return true;
}
void TestGame::render()
{
  //Clear Background
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glUseProgram(program);
  glEnableVertexAttribArray(attribute_coord2d);
  glEnableVertexAttribArray(attribute_v_color);
  
  t1.render(attribute_coord2d, attribute_v_color);
  t2.render(attribute_coord2d, attribute_v_color);
  t3.render(attribute_coord2d, attribute_v_color);

  glDisableVertexAttribArray(attribute_v_color);
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
