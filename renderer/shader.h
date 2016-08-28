#ifndef __RENDERER_SHADER_H
#define __RENDERER_SHADER_H
#include <GL/glew.h>
#include <vector>
class Shader {
private:
  Shader() {}
protected:
  char * shader_contents;
  GLuint object;
  auto printLog() -> void;
public:
  auto printLog(GLuint object) -> void;
  Shader(const char* filename);
  virtual ~Shader();
  virtual auto compile() -> bool = 0; //Linking is done by the program.
  virtual operator GLuint();
  
};
class FragmentShader: public Shader {
public:
  FragmentShader(const char* filename): Shader(filename) {};
  virtual auto compile() -> bool;
};
class VertexShader: public Shader {
public:
  VertexShader(const char* filename): Shader(filename) {};
  virtual auto compile() -> bool;
};
auto link(std::vector<Shader*> &shaders) -> GLuint;
#endif