#include "input.h"
#include "sprite.h"
#include "levels.h"

u8 mouse;
u8 gamepad;
u8 previousMouse;
u8 previousGamepad;
vec2 previousPos;

bool isPlantSelected(Context& ctx){
    return ctx.input.selectedPlant != nullptr;
}

void updateInput(Context& ctx){
    mouse = *MOUSE_BUTTONS;
    gamepad = *GAMEPAD1;

    ctx.input.pos.x = *MOUSE_X;
    ctx.input.pos.y = *MOUSE_Y;

    ctx.input.pressedXButton = (gamepad & (gamepad ^ previousGamepad)) & BUTTON_1;
    ctx.input.pressedLeftMouse = (mouse & (mouse ^ previousMouse)) & MOUSE_LEFT;
    ctx.input.pressedRightMouse = (mouse & (mouse ^ previousMouse)) & MOUSE_RIGHT;

    previousMouse = mouse;
    previousGamepad = gamepad;
    previousPos = ctx.input.pos;
}

void checkGridInput(Context& ctx){
    if(isPlantSelected(ctx)){
        Tile selectedTile = getMouseTile(ctx);
        if(tileIsValid(selectedTile) && ctx.input.pressedLeftMouse){
            createPlant(ctx, *ctx.input.selectedPlant, ctx.level.grid[selectedTile.pos.y][selectedTile.pos.x]);
        }
    }//else{ -> NOT WORKING
    //    Tile selectedTile = getAnyTile(ctx);
    //    if(tileIsValid(selectedTile) && ctx.input.pressedXButton){
    //        ctx.level.grid[selectedTile.pos.y][selectedTile.pos.x].empty = true;
    //        ctx.level.grid[selectedTile.pos.y][selectedTile.pos.x].plant.active = false;
    //    }
    //}
}

void checkSunInput(Context& ctx){
    for(u8 i = 0; i < MAX_SUN_ON_SCREEN; i++){
        if(ctx.level.suns[i].active){
            Rect sun = Rect(ctx.level.suns[i].pos.x, ctx.level.suns[i].pos.y, SUN_FRAME_WIDTH, SUN_FRAME_HEIGHT);
            if(ctx.input.pressedLeftMouse && inRect(ctx.input.pos, sun) && !isPlantSelected(ctx)){
                getSun(ctx, i);
                return;
            }
        }
    }
}

void checkUiInput(Context& ctx){
    for(u8 i = 0; i < MAX_AVALIABLE_PLANTS; i++){
        if(ctx.level.avaliablePlants[i].active){
            if(inRect(ctx.input.pos, Rect(21+17*i, 4, 16, 22)) && ctx.input.pressedLeftMouse && 
            ctx.level.sunAmmount >= ctx.level.avaliablePlants[i].cost && ctx.level.avaliablePlants[i].lastActive - ctx.frames <= 0){
                ctx.input.selectedPlant = &ctx.level.avaliablePlants[i];
            }
        }
    }

    if(ctx.input.pressedRightMouse && isPlantSelected(ctx)){
        ctx.input.selectedPlant = nullptr;
    }
}

void inputLevel(Context& ctx){
    updateInput(ctx);
    checkGridInput(ctx);
    checkSunInput(ctx);
    checkUiInput(ctx);
}

void inputStart(Context& ctx){
    updateInput(ctx);

    if(inRect(ctx.input.pos, Rect(42, 120, 76, 10))){
        startSprite.colors = 0x240;
        if(ctx.input.pressedLeftMouse){
            ctx.scene = Scene(++ctx.currentLevel);
            createLevel1(ctx);
        }
    }else{
        startSprite.colors = 0x140;
    }
}

void inputWon(Context& ctx){
    updateInput(ctx);

    if(inRect(ctx.input.pos, Rect(31, 95, 94, 10))){
        levelCompletedSprite.colors = 0x240;
        if(ctx.input.pressedLeftMouse){
            ctx.scene = Scene(++ctx.currentLevel);
            if(ctx.currentLevel == 2){
                createLevel2(ctx);
            }else if(ctx.currentLevel == 3){
                createLevel3(ctx);
            }
        }
    }else{
        levelCompletedSprite.colors = 0x140;
    }
}

void inputGameOver(Context& ctx){
    updateInput(ctx);

    if(inRect(ctx.input.pos, Rect(33, 95, 93, 10))){
        gameOverSprite.colors = 0x240;
        if(ctx.input.pressedLeftMouse){
            ctx.scene = Scene(ctx.currentLevel);
            if(ctx.currentLevel == 1){
                createLevel1(ctx);
            }else if(ctx.currentLevel == 2){
                createLevel2(ctx);
            }else if(ctx.currentLevel == 3){
                createLevel3(ctx);
            }
        }
    }else{
        gameOverSprite.colors = 0x140;
    }
}