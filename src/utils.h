#pragma once

#include <stdint.h>

// signed
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;

// unsigned
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

// float
typedef float f32;

struct Rect {
  s16 x, y;
  s16 w, h;
  Rect(s16 x, s16 y, s16 w, s16 h) : x(x), y(y), w(w), h(h) {}
};

// functions
#define inRange(x, a, b) ((x) >= (a) && (x) <= (b))
#define inRect(point, rect) (inRange(point.x, rect.x, rect.x+rect.w) && inRange(point.y, rect.y, rect.y+rect.h))
#define inCollision(a, b) (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y)

#define sign(x) \
  ({ __typeof__(x) _x = (x); \
     (__typeof__(x))(_x < 0 ? -1 : 1); })

#define min(a, b) \
  ({ __typeof__(a) _a = (a); \
     __typeof__(b) _b = (b); \
     _a < _b ? _a : _b; })

#define max(a, b) \
  ({ __typeof__(a) _a = (a); \
     __typeof__(b) _b = (b); \
     _a > _b ? _a : _b; })

#define constrain(val, min, max) ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))

// vec2
typedef struct vec2 {
    s16 x, y;
    vec2() : x(0), y(0) {};
    vec2(s16 x, s16 y) : x(x), y(y) {};
} vec2;