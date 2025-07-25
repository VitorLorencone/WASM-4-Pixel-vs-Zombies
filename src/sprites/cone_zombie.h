#pragma once

#include "../utils.h"

#define CONE_ZOMBIE_WIDTH 32
#define CONE_ZOMBIE_HEIGHT 33
#define CONE_ZOMBIE_FLAGS BLIT_2BPP
#define CONE_ZOMBIE_FRAME_COUNT 2
#define CONE_ZOMBIE_FRAME_WIDTH 16
#define CONE_ZOMBIE_FRAME_HEIGHT 33
#define CONE_ZOMBIE_FPS 2

const u8 coneZombieData[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x40, 0x00, 0x00, 0x15, 0x40, 0x00, 0x00, 0x5a, 0x40, 0x00, 0x00, 0x5a, 0x40, 0x00, 0x01, 0x66, 0x40, 0x00, 0x01, 0x66, 0x40, 0x00, 0x05, 0xea, 0x40, 
    0x00, 0x05, 0xea, 0x40, 0x00, 0x56, 0xba, 0x40, 0x00, 0x56, 0xba, 0x40, 0x00, 0x6e, 0xaf, 0x50, 0x00, 0x6e, 0xaf, 0x50, 0x00, 0x6b, 0xaa, 0x90, 0x00, 0x6b, 0xaa, 0x90, 0x00, 0x5a, 0xff, 0x90, 0x00, 0x5a, 0xff, 0x90, 0x01, 0x55, 0xaa, 0x50, 
    0x01, 0x55, 0xaa, 0x50, 0x05, 0xa9, 0x55, 0x40, 0x05, 0xa9, 0x55, 0x40, 0x07, 0x6b, 0xfa, 0x40, 0x07, 0x6b, 0xfa, 0x40, 0x07, 0xe9, 0xfa, 0x40, 0x07, 0xe9, 0xfa, 0x40, 0x06, 0xab, 0xfa, 0x40, 0x06, 0xab, 0xfa, 0x40, 0x05, 0xf6, 0xaa, 0x40, 
    0x05, 0xf6, 0xaa, 0x40, 0x01, 0x55, 0xa9, 0x40, 0x01, 0x55, 0xa9, 0x40, 0x01, 0xd7, 0xa5, 0x00, 0x01, 0xd7, 0xa9, 0x40, 0x01, 0xaa, 0xbd, 0x40, 0x55, 0xaa, 0xbe, 0x50, 0x55, 0x95, 0xfe, 0x50, 0x6b, 0xe6, 0xdf, 0x90, 0x6b, 0xe6, 0xdf, 0x90, 
    0x67, 0x9b, 0x7f, 0x94, 0x67, 0x9b, 0x7f, 0x94, 0x57, 0x5f, 0x7f, 0xe4, 0x57, 0x5f, 0x7f, 0xe4, 0x05, 0x5b, 0x77, 0xe4, 0x05, 0x5b, 0x77, 0xe4, 0x00, 0x16, 0xf6, 0xf4, 0x00, 0x16, 0xf6, 0xf4, 0x00, 0x1a, 0xb6, 0xf4, 0x00, 0x1a, 0xb6, 0xf4, 
    0x00, 0x1a, 0xd9, 0x74, 0x00, 0x1a, 0xd9, 0x74, 0x00, 0x1f, 0x56, 0xf4, 0x00, 0x1f, 0x56, 0xf4, 0x00, 0x16, 0x56, 0x54, 0x00, 0x05, 0x96, 0x54, 0x00, 0x16, 0xd5, 0x90, 0x00, 0x05, 0xb5, 0x90, 0x00, 0x5f, 0x55, 0xd0, 0x00, 0x17, 0xd5, 0xd0, 
    0x00, 0x6a, 0x46, 0x90, 0x00, 0x1a, 0x96, 0x90, 0x00, 0x55, 0x45, 0x50, 0x00, 0x15, 0x55, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const u8 coneZombieAttackingData[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x40, 0x00, 0x00, 0x15, 0x40, 0x00, 0x00, 0x5a, 0x40, 0x00, 0x00, 0x5a, 0x40, 0x00, 0x01, 0x66, 0x40, 0x00, 0x01, 0x66, 0x40, 0x00, 0x05, 0xea, 0x40, 0x00, 0x05, 0xea, 0x40, 
    0x00, 0x56, 0xba, 0x40, 0x00, 0x56, 0xba, 0x40, 0x00, 0x6e, 0xaf, 0x50, 0x00, 0x6e, 0xaf, 0x50, 0x00, 0x6b, 0xaa, 0x90, 0x00, 0x6b, 0xaa, 0x90, 0x00, 0x5a, 0xff, 0x90, 0x00, 0x5a, 0xff, 0x90, 0x01, 0x55, 0xaa, 0x50, 0x01, 0x55, 0xaa, 0x50, 
    0x05, 0xa9, 0x55, 0x40, 0x05, 0xa9, 0x55, 0x40, 0x07, 0x6b, 0xfa, 0x40, 0x07, 0x6b, 0xfa, 0x40, 0x07, 0xe9, 0xfa, 0x40, 0x07, 0xe9, 0xfa, 0x40, 0x06, 0xab, 0xfa, 0x40, 0x06, 0xab, 0xfa, 0x40, 0x05, 0xf6, 0xaa, 0x40, 0x05, 0xf6, 0xaa, 0x40, 
    0x15, 0xd7, 0xa9, 0x40, 0x05, 0x55, 0xa9, 0x40, 0x19, 0xaa, 0xa5, 0x00, 0x05, 0xd7, 0xa5, 0x00, 0x19, 0x55, 0xad, 0x40, 0x06, 0xaa, 0xad, 0x40, 0x19, 0xeb, 0xfe, 0x50, 0x56, 0x5f, 0x7e, 0x50, 0x17, 0xef, 0x7f, 0x90, 0x69, 0x95, 0xff, 0x90, 
    0x15, 0x55, 0xff, 0x94, 0x57, 0xdf, 0xdf, 0x94, 0x1a, 0x9f, 0xdf, 0xe4, 0x07, 0xdd, 0x7f, 0xe4, 0x15, 0x5d, 0x7a, 0xe4, 0x05, 0x56, 0xba, 0xe4, 0x00, 0x56, 0xbb, 0xf4, 0x00, 0x16, 0xfb, 0xf4, 0x00, 0x16, 0xff, 0xf4, 0x00, 0x06, 0xff, 0xf4, 
    0x00, 0x07, 0xfb, 0xf4, 0x00, 0x07, 0xfb, 0xf4, 0x00, 0x06, 0xfa, 0xf4, 0x00, 0x06, 0xfa, 0xf4, 0x00, 0x05, 0x96, 0x54, 0x00, 0x05, 0x96, 0x54, 0x00, 0x05, 0xb5, 0x90, 0x00, 0x05, 0xb5, 0x90, 0x00, 0x17, 0xd5, 0xd0, 0x00, 0x17, 0xd5, 0xd0, 
    0x00, 0x1a, 0x96, 0x90, 0x00, 0x1a, 0x96, 0x90, 0x00, 0x15, 0x55, 0x50, 0x00, 0x15, 0x55, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};