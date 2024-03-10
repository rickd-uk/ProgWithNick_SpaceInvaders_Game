#include <raylib.h>

#include <string>

#include "game.hpp"

std::string FormatWithLeadingZeros(int number, int width) {
  std::string numberText = std::to_string(number);
  int leadingZeros = width - numberText.length();
  numberText = std::string(leadingZeros, '0') + numberText;

  return numberText;
}

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

    // Display the Score
    DrawTextEx(font, "Score: ", {50, 15}, 34, 2, yellow);
    std::string scoreText = FormatWithLeadingZeros(game.GetScore(), 5);
    DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

    DrawTextEx(font, "High-Score: ", {570, 15}, 34, 2, yellow);
    std::string highScoreText = FormatWithLeadingZeros(game.GetHighScore(), 5);
    DrawTextEx(font, highScoreText.c_str(), {655, 40}, 34, 2, yellow);
    game.Draw();

    EndDrawing();
  }
  CloseWindow();
}

/* g++ -o main *.cpp -lraylib && ./main */

// https://www.youtube.com/watch?v=TGo3Oxdpr5o
