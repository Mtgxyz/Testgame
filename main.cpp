#include <iostream>
#include <cstdlib>
#include <main.h>
#include <SDL.h>
#include <GL/glew.h>
using namespace std;
bool TestGame::init()
{
  GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
  //Compile Vertex shader
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  const char *vs_source =
    //"#version 100\n"  // OpenGL ES 2.0
    "#version 120\n"  // OpenGL 2.1
    "attribute vec2 coord2d;                  "
    "void main(void) {                        "
    "  gl_Position = vec4(coord2d, 0.0, 1.0); "
    "}";
  glShaderSource(vs, 1, &vs_source, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
  if (!compile_ok) {
    cerr << "Error in vertex shader" << endl;
    return false;
  }
  //Compile Fragment shader
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fs_source =
    //"#version 100\n"  // OpenGL ES 2.0
    "#version 120\n"  // OpenGL 2.1
    "void main(void) {        "
    "  gl_FragColor[0] = 0.0; "
    "  gl_FragColor[1] = 0.0; "
    "  gl_FragColor[2] = 1.0; "
    "}";
  glShaderSource(fs, 1, &fs_source, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
  if (!compile_ok) {
    cerr << "Error in fragment shader" << endl;
    return false;
  }
  //Linking
  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    cerr << "Error in glLinkProgram" << endl;
    return false;
  }
  const char* attribute_name = "coord2d";
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (attribute_coord2d == -1) {
    cerr << "Could not bind attribute " << attribute_name << endl;
    return false;
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
  GLfloat triangle_vertices[] = {
    0.0,  0.8,
    -0.8, -0.8,
    0.8, -0.8,
  };
    // Describe our vertices array to OpenGL (it can't guess its format automatically)
    glVertexAttribPointer(
    attribute_coord2d, // attribute
    2,                 // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    triangle_vertices  // pointer to the C array
  );

  // Push each element in buffer_vertices to the vertex shader
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(attribute_coord2d);

  // Display the result
  SDL_GL_SwapWindow(window);
}
TestGame::~TestGame()
{
  glDeleteProgram(program);
}

int main(int argc, char **argv) {
    TestGame game;
    game.start();
    return 0;
}
