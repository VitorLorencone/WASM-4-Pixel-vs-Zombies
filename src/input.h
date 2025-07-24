#pragma once

#include "utils.h"
#include "levels.h"
#include "wasm4.h"

bool isPlantSelected(Context& ctx);
void updateInput(Context& ctx);
void checkGridInput(Context& ctx);
void checkSunInput(Context& ctx);
void checkUiInput(Context& ctx);

void inputLevel(Context& ctx);
void inputStart(Context& ctx);
void inputWon(Context& ctx);
void inputEnd(Context& ctx);
void inputGameOver(Context& ctx);