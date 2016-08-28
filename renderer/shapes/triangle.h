#ifndef __SHAPE_TRIANGLE_HPP
#define __SHAPE_TRIANGLE_HPP
#include <GL/glew.h>
#include <renderer/shapes/float2D.h>
class Triangle {
private:
  float2D A;
  float2D B;
  float2D C; //The three points
public:
  Triangle(float x, float y, float alen, float blen, float clen);
  Triangle(float ax, float ay, float bx, float by, float cx, float cy);
  ~Triangle();
  auto render(GLint attrib) -> bool;
};
#endif