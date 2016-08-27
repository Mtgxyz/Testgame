#include <renderer/main.h>
#include <GL/glew.h>
class TestGame: public MainClass {
private:
  GLuint program;
  GLint attribute_coord2d;
  auto render() -> void;
protected:
  virtual auto tick() -> bool;
  virtual auto init() -> bool;
public:
  TestGame(): MainClass(640,480) {};
  virtual ~TestGame();
  virtual auto stop() -> void;
};