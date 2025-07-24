#pragma once

#include "utils.h"

#define FONT_WIDTH 4
#define FONT_HEIGHT 6

void DrawString(const char* str, s16 x, s16 y, bool color);
void DrawInt(int16_t val, s16 x, s16 y, bool color);
void PutPixel(s16 x, s16 y, u8 color);