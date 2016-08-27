#ifndef __RENDERER_MAIN_H
#define __RENDERER_MAIN_H
#include <SDL.h>
class MainClass {
private:
  MainClass() {};
protected:
  SDL_Window* window;
  virtual auto tick() -> bool = 0;
  virtual auto init() -> bool = 0;
public:
  MainClass(int width, int height);
  virtual ~MainClass();
  virtual auto start() -> void;
  virtual auto stop() -> void =0;
};
#endif