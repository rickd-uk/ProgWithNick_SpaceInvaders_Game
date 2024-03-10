#include <raylib.h>

#include "game.hpp"

int main(void) {
  Color grey = {29, 29, 27, 255};
  Color yellow = {243, 216, 63, 255};

  int offset = 50;
  int width = 750;
  int height = 700;

  InitWindow(width + offset, height + (2 * offset), "Space Invaders");

  Texture2D spaceshipImage = LoadTexture("graphics/spaceship.png");
  // LoadFontEx(name,  size,  codepoints,  codepointcount)
  Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

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
    // DrawLineEx(xy start   ,  xy end,  thickness,   color)
    DrawLineEx({25, 730}, {775, 730}, 3, yellow);

    // DrawTextEx(name,  text to display,   xy_pos,   size,  letter spacing,
    // color)

    if (game.running) {
      DrawTextEx(font, "Level 01", {570, 740}, 34, 2, yellow);
    } else {
      DrawTextEx(font, "Game Over!", {570, 740}, 34, 2, yellow);
    }

    float x = 50.0;
    for (int i = 0; i < game.GetLives(); i++) {
      DrawTextureV(spaceshipImage, {x, 745}, WHITE);
      x += 50;
    }
    game.Draw();

    EndDrawing();
  }
  CloseWindow();
}

/* g++ -o main *.cpp -lraylib && ./main */

// https://www.youtube.com/watch?v=TGo3Oxdpr5o
