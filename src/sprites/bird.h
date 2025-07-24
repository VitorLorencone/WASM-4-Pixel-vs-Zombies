#pragma once

#include "../utils.h"

#define BIRD_WIDTH 20
#define BIRD_HEIGHT 3
#define BIRD_FLAGS BLIT_2BPP
#define BIRD_FRAME_COUNT 2
#define BIRD_FRAME_WIDTH 10
#define BIRD_FRAME_HEIGHT 3
#define BIRD_FPS 4
#define BIRD_1_START_POSITION vec2(35, 29)
#define BIRD_2_START_POSITION vec2(99, 27)

const u8 birdData[15] = {
    0x05, 0x54, 0x01, 0x50, 0x55, 0x51, 0x41, 0x50, 0x05, 0x55, 0x54, 0x15, 0x54, 0x15, 0x55, 
};