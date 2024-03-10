#pragma once
#include <raylib.h>

#include "constants.hpp"

class Laser {
 public:
  Laser(Vector2 position, int speed);
  void Draw();
  void Update();
  bool IsActive() const;  // Getter function
  void SetActive(bool isActive);
  Rectangle getRect();

 private:
  Vector2 position;
  int speed;
  bool active;
};
