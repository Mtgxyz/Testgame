#include <renderer/main.h>
#include <renderer/shader.h>
#include <renderer/shapes/triangle.h>
#include <renderer/shapes/quad.h>
#include <GL/glew.h>
#include <state.h>
class TestGame: public MainClass {
private:
  Triangle t1, t2;
  Quad t3;
  GLuint program;
  GLint attribute_coord2d;
  auto render() -> void;
    void logic();
  VertexShader *vs;
  FragmentShader *fs;
  GLint attribute_v_color;
  GameState state;
  GLint uniform_m_transform;
protected:
  virtual auto tick() -> bool;
  virtual auto init() -> bool;
public:
  TestGame(): MainClass(640,480), t1(0.0, 0.0, 0.5, 1.0, 1.0, 0.0), t2(1.0,0.0,1.5,1.0,2.0,0.0), t3(0.5,1.0,0.5,2.0,1.5,2.0,1.5,1.0) {
    state.bright=true;
    state.brightness=0.0;
  };
  virtual ~TestGame();
  virtual auto stop() -> void;
};