#include <raylib.h>

#include "game.hpp"

int main(void) {
  Color grey = {29, 29, 27, 255};
  int width = 750;
  int height = 700;

  InitWindow(width, height, "Space Invaders");
  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose()) {
    game.HandleInput();

    BeginDrawing();
    ClearBackground(grey);

    game.Draw();

    EndDrawing();
  }
  CloseWindow();
}
