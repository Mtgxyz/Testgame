#ifndef __SHAPE_TRIANGLE_HPP
#define __SHAPE_TRIANGLE_HPP
#include <GL/glew.h>
#include <renderer/shapes/float2D.h>
class Triangle {
private:
  GLuint vbo_triangle, vbo_triangle_colors;
  float2D A;
  float2D B;
  float2D C; //The three points
  bool useColors;
public:
  Triangle(float x, float y, float alen, float blen, float clen);
  Triangle(float ax, float ay, float bx, float by, float cx, float cy);
  ~Triangle();
  auto init(GLfloat * colors=nullptr, int size=0) -> void;
  auto render(GLint attrib, GLint colorAttrib) -> bool;
};
#endif