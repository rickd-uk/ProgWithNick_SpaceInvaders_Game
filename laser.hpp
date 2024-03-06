#pragma once
#include <raylib.h>

class Laser {
 public:
  Laser(Vector2 position, int speed);
  void Draw();
  void Update();
  bool IsActive() const; // Getter function
  //
 private:
  Vector2 position;
  int speed;
  bool active;
};
