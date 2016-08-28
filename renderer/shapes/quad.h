#ifndef __SHAPE_QUAD_HPP
#define __SHAPE_QUAD_HPP
#include <GL/glew.h>
#include <renderer/shapes/float2D.h>
#include <renderer/shapes/triangle.h>
class Quad {
private:
  GLuint vbo_triangle;
  Triangle a, b;
public:
  Quad(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy);
  ~Quad();
  auto init(GLfloat * colors) -> void;
  auto render(GLint attrib, GLint colorAttrib) -> bool;
  auto setPos(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy) -> void;
  auto update(GLfloat* colors) -> void;
};
#endif