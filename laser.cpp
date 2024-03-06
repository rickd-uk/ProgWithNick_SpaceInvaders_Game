#include "laser.hpp"

#include <iostream>

Laser::Laser(Vector2 position, int speed): position(position), speed(speed), active(true) {

}

bool Laser::IsActive() const { return active; }

void Laser::Draw() {
  if (active)
    DrawRectangle(position.x, position.y, 4, 15, YELLOW);
}

void Laser::Update() {
  position.y -= speed;

  if (active) {
    if (position.y < 0 || position.y > GetScreenHeight()) {
      active = false;
      std::cout << "Laser is inactive\n" << std::endl;
    }
  }
}
