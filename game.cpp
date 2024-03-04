#include "game.hpp"

Game::Game() {}

Game::~Game() {}

void Game::Draw() {
  spaceship.Draw();
  // TODO
}

void Game::HandleInput() {
  if (IsKeyDown(KEY_LEFT)) {
    spaceship.MoveLeft();
  } else if (IsKeyDown(KEY_RIGHT)) {
    spaceship.MoveRight();
  }
}
