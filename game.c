#include <raylib.h>

int main(void) {

  Color grey = {29, 29, 27, 255};
  int width = 750;
  int height = 700;

  InitWindow(width, height, "Space Invaders");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(grey);

    EndDrawing();
  }
  CloseWindow();
}
