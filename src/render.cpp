#include "render.h"
#include "entities.h"
#include "levels.h"
#include "font.h"

void initPalette(){
    PALETTE[0] = PALETTE_1_COLOR_0;
    PALETTE[1] = PALETTE_1_COLOR_1;
    PALETTE[2] = PALETTE_1_COLOR_2;
    PALETTE[3] = PALETTE_1_COLOR_3;
}

void renderFrame(vec2 pos, Sprite& sprite, u16 color){
    *DRAW_COLORS = color;
    blitSub(*sprite.data, pos.x, pos.y, sprite.frameWidth, sprite.frameHeight, 0, 0, sprite.width, BLIT_2BPP);
}

void renderSprite(Context& ctx, vec2 pos, Sprite& sprite, u16 color){
    *DRAW_COLORS = color;
    if(sprite.animate){
        s16 interval = FRAMES_PER_SECOND/sprite.fps;
        s16 currentFrame = (ctx.frames%(sprite.frameCount*interval))/interval;
        u16 srcX = ((u16) currentFrame)*sprite.frameWidth;
        blitSub(*sprite.data, pos.x, pos.y, sprite.frameWidth, sprite.frameHeight, srcX, 0, sprite.width, BLIT_2BPP);
    }else{
        blit(*sprite.data, pos.x, pos.y, sprite.width, sprite.height, BLIT_2BPP);
    }
}

void renderBackground(Context& ctx){
    renderSprite(ctx, vec2(0,0), backgroundSprite, backgroundSprite.colors);

    for(s8 i = 0; i < BACKGROUND_ENTITIES; i++){
        BackgroundEntity& ent = ctx.level.backgroundEntity[i];
        renderSprite(ctx, ent.pos, *ent.sprite, ent.sprite->colors);

        if(ctx.frames % (FRAMES_PER_SECOND/ent.speed) == 0){
            ent.pos.x -= 1;
            if(ent.pos.x + ent.sprite->width + OFFSET_BACKGROUND_MOVEMENT <= 0){
                ent.pos.x = SCREEN_SIZE;
            }
        }
    }
}

void renderGridSelection(Context& ctx){
    if(ctx.input.selectedPlant != nullptr){
        Tile selectedTile = getMouseTile(ctx);
        *DRAW_COLORS = 0x40;
        if(tileIsValid(selectedTile)){
            rect((selectedTile.pos.x+TILE_X_START)*TILE_WIDTH+2, (selectedTile.pos.y+TILE_Y_START)*TILE_HEIGHT+2, 12, 12);
        }
    }
}

void renderSuns(Context& ctx) {
    for(u8 i = 0; i < MAX_SUN_ON_SCREEN; i++){
        if(ctx.level.suns[i].active){
            renderSprite(ctx, ctx.level.suns[i].pos, sunSprite, sunSprite.colors);
        }
    }
}

const char* int_to_3digits(s16 value) {
    static char buf[4];  // 3 dígitos + '\0'

    if (value < 0) value = 0;
    if (value > 999) value = 999;

    buf[0] = '0' + (char)(value / 100);
    buf[1] = '0' + (char)((value / 10) % 10);
    buf[2] = '0' + (char)(value % 10);
    buf[3] = '\0';

    return buf;
}

void renderUI(Context& ctx){
    renderSprite(ctx, vec2(UI_START_X, UI_START_Y), uiSprite, uiSprite.colors);
    DrawString(int_to_3digits(ctx.level.sunAmmount), 6, 20, 0);
    
    for(u8 i = 0; i < MAX_AVALIABLE_PLANTS; i++){
        if(ctx.level.avaliablePlants[i].active){
            if(ctx.level.avaliablePlants[i].lastActive - ctx.frames > 0){
                *DRAW_COLORS = 0x3;
                rect(22+17*i, 5, 14, 14);
            }

            if(ctx.input.selectedPlant == &ctx.level.avaliablePlants[i]){
                *DRAW_COLORS = 0x30;
                rect(21+17*i, 4, 16, 22);
                *DRAW_COLORS = 0x3;
                rect(21+17*i, 19, 16, 6);
            }

            renderFrame(vec2(21+17*i,4), *ctx.level.avaliablePlants[i].sprite, ctx.level.avaliablePlants[i].sprite->colors);
            DrawString(int_to_3digits(ctx.level.avaliablePlants[i].cost), 24 + 17*i, 20, 1);
        }
    }
}

void renderPlants(Context& ctx){
    for (s8 y = 0; y < TILE_ROWS; y++) {
        for (s8 x = 0; x < TILE_COLUMNS; x++) {
            if(ctx.level.grid[y][x].empty == false){
                if(ctx.level.grid[y][x].plant.state == PLANT_ATTACKED){
                    renderSprite(ctx, ctx.level.grid[y][x].plant.pos, *ctx.level.grid[y][x].plant.sprite, 0x4440);
                }else{
                    if(ctx.level.grid[y][x].plant.type == SUNFLOWER && ctx.level.grid[y][x].plant.state == SUNFLOWER_SPECIAL){
                        renderSprite(ctx, ctx.level.grid[y][x].plant.pos, *ctx.level.grid[y][x].plant.sprite, 0x1140);
                    }else{
                        renderSprite(ctx, ctx.level.grid[y][x].plant.pos, *ctx.level.grid[y][x].plant.sprite, ctx.level.grid[y][x].plant.sprite->colors);
                    }
                }
            }
        }
    }
}

void renderZombies(Context& ctx){
    for(u8 lane = 0; lane < TILE_ROWS; lane++){
        for(u8 i = 0; i < MAX_ZOMBIES_PER_WAVE; i++){
            ZombieEntity* zombie = &ctx.level.waves[ctx.level.waveId].zombies[i];
            if(zombie->active && zombie->pos.y == TILE_Y_START*TILE_HEIGHT + lane * TILE_HEIGHT-zombie->offset){
                if(zombie->state == ZOMBIE_ATTACKED || zombie->state == ZOMBIE_ATTACKING_ATTACKED){
                    renderSprite(ctx, zombie->pos, *zombie->sprite, 0x4440);
                }else{
                    renderSprite(ctx, zombie->pos, *zombie->sprite, zombie->sprite->colors);
                }
            }
        }
    }
}

void renderProjectiles(Context& ctx){
    for(u8 i = 0; i < MAX_PROJECTILES; i++){
        if(ctx.level.projectiles[i].active){
            renderSprite(ctx, ctx.level.projectiles[i].pos, *ctx.level.projectiles[i].sprite, ctx.level.projectiles[i].sprite->colors);
        }
    }
}

void renderLevel(Context& ctx){
    renderBackground(ctx);
    renderUI(ctx);
    renderPlants(ctx);
    renderGridSelection(ctx);
    renderZombies(ctx);
    renderProjectiles(ctx);
    renderSuns(ctx);
}

void renderStart(Context& ctx){
    renderSprite(ctx, vec2(0,0), backgroundSprite, backgroundSprite.colors);
    renderSprite(ctx, vec2(SCREEN_SIZE/2 - START_WIDTH/2, SCREEN_SIZE/2 - 25), startSprite, startSprite.colors);
}

void renderWon(Context& ctx){
    renderSprite(ctx, vec2(0,0), backgroundSprite, backgroundSprite.colors);
    renderSprite(ctx, vec2(SCREEN_SIZE/2 - LEVEL_COMPLETED_WIDTH/2, SCREEN_SIZE/2 - 25), levelCompletedSprite, levelCompletedSprite.colors);
}

void renderEnd(Context& ctx){
    renderSprite(ctx, vec2(0,0), backgroundSprite, backgroundSprite.colors);
    renderSprite(ctx, vec2(SCREEN_SIZE/2 - WIN_WIDTH/2, SCREEN_SIZE/2 - 25), winSprite, winSprite.colors);
}

void renderGameOver(Context& ctx){
    renderSprite(ctx, vec2(0,0), backgroundSprite, backgroundSprite.colors);
    renderSprite(ctx, vec2(SCREEN_SIZE/2 - GAME_OVER_WIDTH/2, SCREEN_SIZE/2 - 25), gameOverSprite, gameOverSprite.colors);
}