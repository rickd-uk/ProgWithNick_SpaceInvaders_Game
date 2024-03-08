#include <raylib.h>

#include "game.hpp"
#include "obstacle.hpp"

int main(void) {
  Color grey = {29, 29, 27, 255};
  int width = 750;
  int height = 700;

  InitWindow(width, height, "Space Invaders");
  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose()) {
    game.HandleInput();
    game.Update();

    BeginDrawing();
    ClearBackground(grey);

    game.Draw();

    EndDrawing();
  }
  CloseWindow();
}

// bi() {     gcc *.cpp -o main -lstdc++ -lraylib && ./main; }

/* bi() {     gcc main.cpp spaceship.cpp game.cpp laser.cpp -o main -lraylib
 -lstdc++ && ./main; }   */

// https://www.youtube.com/watch?v=TGo3Oxdpr5o
