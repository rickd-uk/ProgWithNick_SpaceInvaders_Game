#pragma once
#include <raylib.h>

#include <vector>

#include "constants.hpp"
#include "laser.hpp"

class Spaceship {
 public:
  Spaceship();
  ~Spaceship();
  void Draw();
  void MoveLeft();
  void MoveRight();
  void FireLaser();
  void Reset();
  Rectangle getRect();

  std::vector<Laser> lasers;

 private:
  Texture2D image;
  Vector2 position;
  double lastFireTime;
  constexpr static int offset = 100;
  // constrain spacehip within borders left and right
};
