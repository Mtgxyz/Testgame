#include <renderer/shapes/triangle.h>
Triangle::Triangle(float x, float y, float alen, float blen, float clen)
{
  A.x=x;
  A.y=y;
  
}
Triangle::Triangle(float ax, float ay, float bx, float by, float cx, float cy)
{
  A.x=ax-1.0;
  A.y=ay-1.0;
  B.x=bx-1.0;
  B.y=by-1.0;
  C.x=cx-1.0;
  C.y=cy-1.0;
}

Triangle::~Triangle()
{
  
}
bool Triangle::render(GLint attrib)
{
  GLfloat triangle_vertices[] = {
    A.x, A.y,
    B.x, B.y,
    C.x, C.y
  };
  glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, triangle_vertices);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  return true;
}
