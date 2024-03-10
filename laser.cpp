#include "laser.hpp"

#include <iostream>

Laser::Laser(Vector2 position, int speed)
    : position(position), speed(speed), active(true) {}

bool Laser::IsActive() const { return active; }

void Laser::SetActive(bool isActive) { active = isActive; }

void Laser::Draw() {
  if (active) DrawRectangle(position.x, position.y, width, height, YELLOW);
}

void Laser::Update() {
  position.y -= speed;

  if (active) {
    if (position.y < G_SPACESHIP_OFFSET ||
	position.y > GetScreenHeight() - G_SPACESHIP_OFFSET) {
      active = false;
      // std::cout << "Laser is inactive\n" << std::endl;
    }
  }
}

Rectangle Laser::getRect() {
  Rectangle rec;
  rec.x = position.x;
  rec.y = position.y;
  rec.width = width;
  rec.height = height;

  return rec;
}

