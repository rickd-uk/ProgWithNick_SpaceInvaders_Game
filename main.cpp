#include <raylib.h>

#include "game.hpp"

int main(void) {
  Color grey = {29, 29, 27, 255};
  Color yellow = {243, 216, 63, 255};

  int offset = 50;
  int width = 750;
  int height = 700;

  InitWindow(width + offset, height + (2 * offset), "Space Invaders");
  SetTargetFPS(60);

  Game game;
  while (!WindowShouldClose()) {
    game.HandleInput();
    game.Update();

    BeginDrawing();
    ClearBackground(grey);
    // DrawRectangleRoundedLines({rectangle coords}, Roundness, No_of_segments =
    // smoothness, Border Thickness, color)
    DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
    game.Draw();

    EndDrawing();
  }
  CloseWindow();
}

// bi() {     gcc *.cpp -o main -lstdc++ -lraylib && ./main; }

/* bi() {     gcc main.cpp spaceship.cpp game.cpp laser.cpp -o main -lraylib
 -lstdc++ && ./main; }   */

// https://www.youtube.com/watch?v=TGo3Oxdpr5o
