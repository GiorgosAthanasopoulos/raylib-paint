#include <raylib.h>

#include "config.h"
#include "types.h"
#include "utils.h"

// FIX: Hovering over and clicking on a color picker box doesn't
// select the color!

void Update(Paint *paint) {
  int renderW = GetRenderWidth(), renderH = GetRenderHeight();
  if (renderW != paint->w || renderH != paint->h) {
    paint->w = renderW;
    paint->h = renderH;
    ClearBackground(WIN_BG_COLOR);
  }

  if (IsKeyPressed(ERASER_KEY)) {
    Color temp = paint->color;
    paint->color = ColorsEqual(WIN_BG_COLOR, paint->color) ? paint->oldColor
                                                           : WIN_BG_COLOR;
    paint->oldColor = temp;
  }
  if (IsKeyPressed(CLEAR_CANVAS_KEY)) {
    ClearBackground(WIN_BG_COLOR);
  }
  if (IsKeyPressed(RADIUS_MINUS_KEY)) {
    paint->radius -= 1;
  } else if (IsKeyPressed(RADIUS_PLUS_KEY)) {
    paint->radius += 1;
  } else if (IsKeyPressed(RADIUS_ZERO_KEY)) {
    paint->radius = PEN_RADIUS;
  }

  paint->interferingWithUI = false;
  float centerW = (float)paint->w / 2;
  float colorPickerBarW = paint->colors.size() * COLOR_PICKER_W;
  Vector2 mousePos = GetMousePosition();
  for (int i = 0; i < paint->colors.size(); ++i) {
    Vector2 pos = {centerW - colorPickerBarW / 2 + i * COLOR_PICKER_W,
                   (float)paint->h - 2 * COLOR_PICKER_H};
    Rectangle rect = {pos.x, pos.y, COLOR_PICKER_W, COLOR_PICKER_H};

    if (MouseHovered(rect, mousePos)) {
      paint->interferingWithUI = true;
      if (IsMouseButtonPressed(DRAW_KEY)) {
        paint->oldColor = paint->color;
        paint->color = paint->colors[i];
      }
    }
  }
}

void Draw(Paint *paint) {
  BeginDrawing();
  Vector2 mousePos = GetMousePosition();
  float centerW = (float)paint->w / 2;
  float colorPickerBarW = paint->colors.size() * COLOR_PICKER_W;

  for (int i = 0; i < paint->colors.size(); ++i) {
    Vector2 pos = {centerW - colorPickerBarW / 2 + i * COLOR_PICKER_W,
                   (float)paint->h - 2 * COLOR_PICKER_H};
    Rectangle rect = {pos.x, pos.y, COLOR_PICKER_W, COLOR_PICKER_H};
    DrawRectangleRec(rect, paint->colors[i]);
  }

  if (IsMouseButtonDown(DRAW_KEY) && !paint->interferingWithUI) {
    DrawCircle(mousePos.x, mousePos.y, paint->radius, paint->color);
  }

  EndDrawing();
}

int main() {
  Paint paint = {0};
  paint.w = WIN_W, paint.h = WIN_H;
  paint.radius = PEN_RADIUS, paint.color = DEFAULT_DRAWING_COLOR;
  paint.colors = {RED,   BLUE,  YELLOW, WHITE, BLACK,
                  BROWN, GREEN, ORANGE, PURPLE};

  SetConfigFlags(WIN_FLAGS);
  InitWindow(paint.w, paint.h, WIN_TITLE);
  SetTargetFPS(TARGET_FPS);
  ClearBackground(WIN_BG_COLOR);
  SetExitKey(EXIT_KEY);

  while (!WindowShouldClose()) {
    Update(&paint);
    Draw(&paint);
  }

  CloseWindow();
  return 0;
}
