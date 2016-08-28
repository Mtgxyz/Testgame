#include <renderer/shader.h>
#include <SDL.h>
#include <iostream>
using namespace std;
Shader::Shader(const char* filename): object(0)
{
  SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
  if(rw==NULL) throw nullptr; //Load
  
  Sint64 res_size = SDL_RWsize(rw);
  shader_contents=new char[res_size+1]; //Allocate
  
  Sint64 nb_read_total=0, nb_read=1;
  char* buf = shader_contents;
  while(nb_read_total < res_size && nb_read != 0 ) { //Read
    nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
    nb_read_total += nb_read;
    buf += nb_read;
  }
  
  SDL_RWclose(rw); //Cleanup
  if (nb_read_total != res_size) {
    delete[] shader_contents;
    throw nullptr;
  }
  shader_contents[nb_read_total] = '\0';
}

Shader::~Shader()
{
  delete[] shader_contents;
  if(object)
    glDeleteShader(object);
}

Shader::operator GLuint()
{
  return object;
}

void Shader::printLog()
{
  printLog(object);
}

void Shader::printLog(GLuint object)
{
  GLint log_length = 0;
  if(glIsShader(object)) {
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  } else if(glIsProgram(object)) {
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  } else {
    cerr << "printlog: Not a shader or a program" << endl;
    return;
  }
  
  char* log = new char[log_length];
  
  if(glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);
  else
    glGetProgramInfoLog(object, log_length, NULL, log);
  
  cerr << log;
  delete[] log;
}
auto FragmentShader::compile() -> bool {
  const GLchar *source = shader_contents;
  GLuint res = glCreateShader(GL_FRAGMENT_SHADER);
  
  const GLchar* sources[] = {
#ifdef GL_ES_VERSION_2_0
    "#version 100\n" //OpenGL ES 2.0
#else
    "#version 120\n" //OpenGL .1
#endif
    ,source };
  glShaderSource(res, 2, sources, NULL);
    
  glCompileShader(res);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
  if(compile_ok == GL_FALSE) {
    printLog(res);
    glDeleteShader(res);
    return false;
  }
  object=res;
  return true;
}
auto VertexShader::compile() -> bool {
  const GLchar *source = shader_contents;
  GLuint res = glCreateShader(GL_VERTEX_SHADER);
  
  const GLchar* sources[] = {
#ifdef GL_ES_VERSION_2_0
    "#version 100\n" //OpenGL ES 2.0
#else
    "#version 120\n" //OpenGL .1
#endif
    ,source };
  glShaderSource(res, 2, sources, NULL);
    
  glCompileShader(res);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
  if(compile_ok == GL_FALSE) {
    printLog(res);
    glDeleteShader(res);
    return false;
  }
  object=res;
  return true;
}
GLuint link(vector< Shader*> &shaders)
{
  GLint link_ok = GL_FALSE;
  GLuint program=glCreateProgram();
  for(int i=0;i<shaders.size();i++) {
    glAttachShader(program, *shaders[i]);
  }
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (link_ok==GL_FALSE) {
    shaders[0]->printLog(program);
    throw nullptr;
  }
  return program;
}