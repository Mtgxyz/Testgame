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
    A.x, A.y,
    B.x, B.y,
    C.x, C.y
  };
  glGenBuffers(1, &vbo_triangle);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle); //Create VBO
  //Fill VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
  
  //Init colors
  if(!colors)
    useColors=false;
  else {
    useColors=true;
    glGenBuffers(1, &vbo_triangle_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_colors);
    glBufferData(GL_ARRAY_BUFFER, size, colors, GL_STATIC_DRAW);
    
  }
}
Triangle::~Triangle()
{
  glDeleteBuffers(1, &vbo_triangle);
}
bool Triangle::render(GLint attrib, GLint color_attrib)
{
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  if(useColors) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_colors);
    glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
  }
  glDrawArrays(GL_TRIANGLES, 0, 3);
  return true;
}
