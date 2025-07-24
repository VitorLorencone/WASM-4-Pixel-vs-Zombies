#pragma once

#include "utils.h"
#include "sprite.h"
#include "types.h"
#include "wasm4.h"

void initPalette();
void renderFrame(vec2 pos, Sprite& sprite, u16 color);
void renderSprite(Context& ctx, vec2 pos, Sprite& sprite, u16 color);
void renderBackground(Context& ctx);
void renderGridSelection(Context& ctx);
void renderSuns(Context& ctx);
void renderUI(Context& ctx);
void renderPlants(Context& ctx);
void renderZombies(Context& ctx);
void renderProjectiles(Context& ctx);

void renderLevel(Context& ctx);
void renderStart(Context& ctx);
void renderWon(Context& ctx);
void renderEnd(Context& ctx);
void renderGameOver(Context& ctx);