#include <renderer/shapes/quad.h>
void Quad::init(GLfloat* colors)
{
  GLfloat colors1[] = {
    colors[0], colors[1], colors[2],
    colors[3], colors[4], colors[5],
    colors[6], colors[7], colors[8]
  };
  GLfloat colors2[] = {
    colors[3], colors[4], colors[5],
    colors[6], colors[7], colors[8],
    colors[9], colors[10], colors[11]
  };
  a.init(colors1);
  b.init(colors2);
}
Quad::Quad(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy): a(ax, ay, bx, by, dx, dy), b(bx, by, dx, dy, cx, cy)
{
  
}
bool Quad::render(GLint attrib, GLint colorAttrib)
{
  if(a.render(attrib, colorAttrib))
    return b.render(attrib, colorAttrib);
  return false;
}
void Quad::setPos(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy)
{
  a.setPos(ax, ay, bx, by, dx, dy);
  b.setPos(bx, by, dx, dy, cx, cy);
}
void Quad::update(GLfloat* colors)
{
  GLfloat colors1[] = {
    colors[0], colors[1], colors[2],
    colors[3], colors[4], colors[5],
    colors[6], colors[7], colors[8]
  };
  GLfloat colors2[] = {
    colors[3], colors[4], colors[5],
    colors[6], colors[7], colors[8],
    colors[9], colors[10], colors[11]
  };
  a.update(colors1);
  b.update(colors2);
}
Quad::~Quad()
{

}
