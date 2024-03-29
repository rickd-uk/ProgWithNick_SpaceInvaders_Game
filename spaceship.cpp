#include "spaceship.hpp"

Spaceship::Spaceship() {
  image = LoadTexture("graphics/spaceship.png");
  position.x = (float)(GetScreenWidth() - image.width) / 2;
  position.y = GetScreenHeight() - image.height - G_SPACESHIP_OFFSET;
  lastFireTime = 0.0;
}

Spaceship::~Spaceship() { UnloadTexture(image); }

void Spaceship::Draw() { DrawTextureV(image, position, WHITE); }

void Spaceship::MoveLeft() {
  position.x -= 7;
  if (position.x < G_BORDER_OFFSET) {
    position.x = G_BORDER_OFFSET;
  }
}
void Spaceship::MoveRight() {
  position.x += 7;
  if (position.x > GetScreenWidth() - image.width - G_BORDER_OFFSET) {
    position.x = GetScreenWidth() - image.width - G_BORDER_OFFSET;
  }
}

void Spaceship::FireLaser() {
  if ((GetTime() - lastFireTime >= 0.35)) {
    lasers.push_back(
	Laser({position.x + (float)image.width / 2 - 2, position.y}, 6));
    lastFireTime = GetTime();
  }
}

Rectangle Spaceship::getRect() {
  return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset() {
  position.x = (float)(GetScreenWidth() - image.width) / 2;
  position.y = (float)(GetScreenHeight() - image.height - G_SPACESHIP_OFFSET);
  lasers.clear();
}
