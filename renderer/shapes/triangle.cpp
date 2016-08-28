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
auto Triangle::init(GLfloat * colors, int size) -> void {
  GLfloat triangle_vertices[] = {
    A.x, A.y, 0.0, colors[0], colors[1], colors[2],
    B.x, B.y, 0.0, colors[3], colors[4], colors[5],
    C.x, C.y, 0.0, colors[6], colors[7], colors[8]
  };
  glGenBuffers(1, &vbo_triangle);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle); //Create VBO
  //Fill VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
}
Triangle::~Triangle()
{
  glDeleteBuffers(1, &vbo_triangle);
}
bool Triangle::render(GLint attrib, GLint color_attrib)
{
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
  glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
  glDrawArrays(GL_TRIANGLES, 0, 3);
  return true;
}
auto Triangle::setPos(float ax, float ay, float bx, float by, float cx, float cy)  -> void
{
  A.x=ax-1.0;
  A.y=ay-1.0;
  B.x=bx-1.0;
  B.y=by-1.0;
  C.x=cx-1.0;
  C.y=cy-1.0;
}
auto Triangle::update(GLfloat* colors, int size) -> void
{
  glDeleteBuffers(1, &vbo_triangle);
  GLfloat triangle_vertices[] = {
    A.x, A.y, 0.0, colors[0], colors[1], colors[2],
    B.x, B.y, 0.0, colors[3], colors[4], colors[5],
    C.x, C.y, 0.0, colors[6], colors[7], colors[8]
  };
  glGenBuffers(1, &vbo_triangle);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle); //Create VBO
  //Fill VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
}
