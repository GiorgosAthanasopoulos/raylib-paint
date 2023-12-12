#pragma once

#include <raylib.h>

bool ColorsEqual(Color a, Color b) {
  return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

bool MouseHovered(Rectangle rect, Vector2 mousePos) {
  return mousePos.x >= rect.x && mousePos.x <= rect.x + rect.width &&
         mousePos.y >= rect.y && mousePos.y <= rect.y && rect.height;
}
