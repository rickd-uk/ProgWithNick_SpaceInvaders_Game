#include "alien.hpp"
#include <raylib.h>

Alien::Alien(int type, Vector2 position) {
  this->type = type;
  this->position = position;

  switch (type) {
  case 1:
    image = LoadTexture("graphics/alien_1.png");
    break;
  case 2:
    image = LoadTexture("graphics/alien_2.png");
    break;
  case 3:
    image = LoadTexture("graphics/alien_3.png");
    break;
  case 4:
    image = LoadTexture("graphics/alien_4.png");
    break;
  }
}

void Alien::Draw() { DrawTextureV(image, position, WHITE); }

int Alien::GetType() { return type; }
