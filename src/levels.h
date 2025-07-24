#pragma once

#include "types.h"
#include "entities.h"
#include "utils.h"
#include "constants.h"

Tile getTile(Context& ctx, vec2 pos);
Tile getMouseTile(Context& ctx);
Tile getAnyTile(Context& ctx);

bool tileIsValid(Tile tile);
bool hasTimeElapsed(s32 startFrame, s32 currentFrame, s32 delay);
u32 rand();
s16 random(u32 min, u32 max);

void clearTile(Context& ctx, vec2 tile);

void getSun(Context& ctx, u8 index);

void updateTime(Context& ctx);
void updateSun(Context& ctx);
void updatePlants(Context& ctx);
void updateZombies(Context& ctx);
void updateWaves(Context& ctx);
void updateProjectile(Context& ctx);
void updateCollisions(Context& ctx);

void nextWave(Context& ctx);

void initLevel(Context& ctx);
void createLevel1(Context& ctx);
void createLevel2(Context& ctx);
void createLevel3(Context& ctx);

void updateLevel(Context& ctx);