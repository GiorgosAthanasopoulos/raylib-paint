#pragma once

#include <raylib.h>
#include <vector>

typedef struct {
  int w, h;
  int radius;
  Color color, oldColor;
  std::vector<Color> colors;
  bool interferingWithUI;
} Paint;
