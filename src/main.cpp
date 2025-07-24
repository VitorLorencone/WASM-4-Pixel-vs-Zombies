#include "wasm4.h"
#include "types.h"
#include "constants.h"
#include "sprite.h"
#include "input.h"
#include "levels.h"
#include "render.h"

// Todo
// music

Context ctx;

void start() {
    initPalette();
}

void update() {

    switch(ctx.scene){
    
    case START_SCENE:
        renderStart(ctx);
        inputStart(ctx);
        break;

    case LEVEL1_SCENE:
    case LEVEL2_SCENE:
    case LEVEL3_SCENE:
        renderLevel(ctx);
        updateLevel(ctx);
        inputLevel(ctx);
        break;

    case GAME_OVER_SCENE:
        renderGameOver(ctx);
        inputGameOver(ctx);
        break;

    case WON_SCENE:
        renderWon(ctx);
        inputWon(ctx);
        break;

    case END_SCENE:
        renderEnd(ctx);
        break;
    
    default:
        break;
    }

    // Global
    updateTime(ctx);
}