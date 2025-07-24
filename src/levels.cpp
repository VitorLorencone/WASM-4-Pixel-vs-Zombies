#include "levels.h"
#include "sprite.h"
#include "wasm4.h"

u32 seed = 1254739;
s32 lastSun;
s32 waveStartTime;

Tile getTile(Context& ctx, vec2 pos){
    return ctx.level.grid[pos.y][pos.x];
}

Tile getMouseTile(Context& ctx){
    vec2 mousePos = ctx.input.pos;
    Rect grid = Rect(TILE_X_START*TILE_WIDTH, TILE_Y_START*TILE_HEIGHT, GRID_WIDTH-1, GRID_HEIGHT-1);
    if(inRect(mousePos, grid)){
        s16 posX = (mousePos.x)/(TILE_WIDTH) - TILE_X_START;
        s16 posY = mousePos.y/(TILE_HEIGHT) - TILE_Y_START;
        Tile tl = getTile(ctx, vec2(posX, posY));
        if(tl.empty == false){return Tile(vec2(-1, -1));}
        else{return tl;}
    }else{
        return Tile(vec2(-1,-1));
    }
}

Tile getAnyTile(Context& ctx){
    vec2 mousePos = ctx.input.pos;
    Rect grid = Rect(TILE_X_START*TILE_WIDTH, TILE_Y_START*TILE_HEIGHT, GRID_WIDTH-1, GRID_HEIGHT-1);
    if(inRect(mousePos, grid)){
        s16 posX = (mousePos.x)/(TILE_WIDTH) - TILE_X_START;
        s16 posY = mousePos.y/(TILE_HEIGHT) - TILE_Y_START;
        Tile tl = getTile(ctx, vec2(posX, posY));
        return tl;
    }else{
        return Tile(vec2(-1,-1));
    }
}

bool tileIsValid(Tile tile){
    return tile.pos.x != -1 && tile.pos.y != -1;
}

u32 rand(){
    seed = seed * 9737333 + 1559861749;
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

s16 random(u32 min, u32 max){
    return (s16)(min + (rand() % (max - min + 1)));
}

void clearTile(Context& ctx, vec2 tile){
    tracef("%d, %d", tile.x, tile.y);
    ctx.level.grid[tile.y][tile.x].empty = true;
    ctx.level.grid[tile.y][tile.x].plant.active = false;
}

void getSun(Context& ctx, u8 index){
    ctx.level.sunAmmount += SUN_VALUE;
    ctx.level.sunAmmount = constrain(ctx.level.sunAmmount, 0, 975);
    ctx.level.suns[index].active = false;
}

bool hasTimeElapsed(s32 startFrame, s32 currentFrame, s32 delay) {
    return currentFrame - startFrame >= delay;
}

void initLevel(Context& ctx){
    ctx.level.sunAmmount = INIT_SUN_VALUE;

    for (s8 y = 0; y < TILE_ROWS; y++) {
        for (s8 x = 0; x < TILE_COLUMNS; x++) {
            ctx.level.grid[y][x] = Tile(vec2(x, y));
        }
    }
    initBackgroundEntities(ctx.level.backgroundEntity);

    lastSun = ctx.frames + random(SUN_MIN_DELAY, SUN_MAX_DELAY) * FRAMES_PER_SECOND;

    ctx.level.waveId = 0;

    for(s8 i = 0; i < MAX_SUN_ON_SCREEN; i++){
        ctx.level.suns[i].active = false;
    }

    for(s8 i = 0; i < MAX_PROJECTILES; i++){
        ctx.level.projectiles[i].active = false;
    }

    for(s8 i = 0; i < MAX_WAVES; i++){
        for(s8 j = 0; j < MAX_ZOMBIES_PER_WAVE; j++){
            ctx.level.waves[i].zombies[j].active = false;
        }
    }

    ctx.input.selectedPlant = nullptr;

    waveStartTime = ctx.frames;
}

void createLevel1(Context& ctx){
    initLevel(ctx);
    ctx.level.avaliablePlants[0] = sunflowerCard;
    ctx.level.avaliablePlants[1] = peashooterCard;
    
    // Wave 1

    ctx.level.waves[0].zombieAmmount = 2;

    ctx.level.waves[0].lanes[0] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[1] = (u8)random(0, 5);

    ctx.level.waves[0].delays[0] = 1200;
    ctx.level.waves[0].delays[1] = 2400;

    ctx.level.waves[0].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[0].types[1] = NORMAL_ZOMBIE;

    // Wave 2
    ctx.level.waves[1].zombieAmmount = 3;

    ctx.level.waves[1].lanes[0] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[1] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[2] = (u8)random(0, 5);

    ctx.level.waves[1].delays[0] = 60;
    ctx.level.waves[1].delays[1] = 300;
    ctx.level.waves[1].delays[2] = 1200;

    ctx.level.waves[1].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[1].types[1] = NORMAL_ZOMBIE;
    ctx.level.waves[1].types[2] = NORMAL_ZOMBIE;

    // Wave 3
    ctx.level.waves[2].zombieAmmount = 5;

    ctx.level.waves[2].lanes[0] = (u8) random(0, 5);
    ctx.level.waves[2].lanes[1] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[2] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[3] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[4] = (u8)random(0, 5);

    ctx.level.waves[2].delays[0] = 60;
    ctx.level.waves[2].delays[1] = 900;
    ctx.level.waves[2].delays[2] = 960;
    ctx.level.waves[2].delays[3] = 1020;
    ctx.level.waves[2].delays[4] = 1200;

    ctx.level.waves[2].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[2].types[1] = CONE_ZOMBIE;
    ctx.level.waves[2].types[2] = CONE_ZOMBIE;
    ctx.level.waves[2].types[3] = CONE_ZOMBIE;
    ctx.level.waves[2].types[4] = NORMAL_ZOMBIE;
}

void createLevel2(Context& ctx){
    initLevel(ctx);
    ctx.level.avaliablePlants[0] = sunflowerCard;
    ctx.level.avaliablePlants[1] = peashooterCard;
    ctx.level.avaliablePlants[2] = wallnutCard;
    
    // Wave 1

    ctx.level.waves[0].zombieAmmount = 5;

    ctx.level.waves[0].lanes[0] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[1] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[2] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[3] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[4] = (u8)random(0, 5);

    ctx.level.waves[0].delays[0] = 1500;
    ctx.level.waves[0].delays[1] = 2700;
    ctx.level.waves[0].delays[2] = 3000;
    ctx.level.waves[0].delays[3] = 3060;
    ctx.level.waves[0].delays[4] = 3900;

    ctx.level.waves[0].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[0].types[1] = NORMAL_ZOMBIE;
    ctx.level.waves[0].types[2] = NORMAL_ZOMBIE;
    ctx.level.waves[0].types[3] = NORMAL_ZOMBIE;
    ctx.level.waves[0].types[4] = NORMAL_ZOMBIE;

    // Wave 2
    ctx.level.waves[1].zombieAmmount = 5;

    ctx.level.waves[1].lanes[0] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[1] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[2] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[3] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[4] = (u8)random(0, 5);

    ctx.level.waves[1].delays[0] = 60;
    ctx.level.waves[1].delays[1] = 300;
    ctx.level.waves[1].delays[2] = 1200;
    ctx.level.waves[1].delays[3] = 2100;
    ctx.level.waves[1].delays[4] = 2160;

    ctx.level.waves[1].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[1].types[1] = CONE_ZOMBIE;
    ctx.level.waves[1].types[2] = CONE_ZOMBIE;
    ctx.level.waves[1].types[3] = NORMAL_ZOMBIE;
    ctx.level.waves[1].types[4] = CONE_ZOMBIE;

    // Wave 3
    ctx.level.waves[2].zombieAmmount = 6;

    ctx.level.waves[2].lanes[0] = (u8) random(0, 5);
    ctx.level.waves[2].lanes[1] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[2] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[3] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[4] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[5] = (u8)random(0, 5);

    ctx.level.waves[2].delays[0] = 150;
    ctx.level.waves[2].delays[1] = 1200;
    ctx.level.waves[2].delays[2] = 1260;
    ctx.level.waves[2].delays[3] = 1320;
    ctx.level.waves[2].delays[4] = 1800;
    ctx.level.waves[2].delays[5] = 2100;

    ctx.level.waves[2].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[2].types[1] = CONE_ZOMBIE;
    ctx.level.waves[2].types[2] = NORMAL_ZOMBIE;
    ctx.level.waves[2].types[3] = CONE_ZOMBIE;
    ctx.level.waves[2].types[4] = BUCKET_ZOMBIE;
    ctx.level.waves[2].types[5] = BUCKET_ZOMBIE;
}

void createLevel3(Context& ctx){
    initLevel(ctx);
    ctx.level.avaliablePlants[0] = sunflowerCard;
    ctx.level.avaliablePlants[1] = peashooterCard;
    ctx.level.avaliablePlants[2] = wallnutCard;
    ctx.level.avaliablePlants[3] = repeaterCard;
    ctx.level.avaliablePlants[4] = potatomineCard;
    
    // Wave 1

    ctx.level.waves[0].zombieAmmount = 5;

    ctx.level.waves[0].lanes[0] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[1] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[2] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[3] = (u8)random(0, 5);
    ctx.level.waves[0].lanes[4] = (u8)random(0, 5);

    ctx.level.waves[0].delays[0] = 1200;
    ctx.level.waves[0].delays[1] = 2400;
    ctx.level.waves[0].delays[2] = 2700;
    ctx.level.waves[0].delays[3] = 2760;
    ctx.level.waves[0].delays[4] = 3000;

    ctx.level.waves[0].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[0].types[1] = BUCKET_ZOMBIE;
    ctx.level.waves[0].types[2] = NORMAL_ZOMBIE;
    ctx.level.waves[0].types[3] = CONE_ZOMBIE;
    ctx.level.waves[0].types[4] = CONE_ZOMBIE;

    // Wave 2
    ctx.level.waves[1].zombieAmmount = 8;

    ctx.level.waves[1].lanes[0] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[1] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[2] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[4] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[5] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[6] = (u8)random(0, 5);
    ctx.level.waves[1].lanes[7] = (u8)random(0, 5);

    ctx.level.waves[1].delays[0] = 1200;
    ctx.level.waves[1].delays[1] = 1800;
    ctx.level.waves[1].delays[2] = 2100;
    ctx.level.waves[1].delays[3] = 2160;
    ctx.level.waves[1].delays[4] = 2700;
    ctx.level.waves[1].delays[5] = 2760;
    ctx.level.waves[1].delays[6] = 3600;
    ctx.level.waves[1].delays[7] = 4200;

    ctx.level.waves[1].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[1].types[1] = CONE_ZOMBIE;
    ctx.level.waves[1].types[2] = NORMAL_ZOMBIE;
    ctx.level.waves[1].types[3] = BUCKET_ZOMBIE;
    ctx.level.waves[1].types[4] = BUCKET_ZOMBIE;
    ctx.level.waves[1].types[5] = CONE_ZOMBIE;
    ctx.level.waves[1].types[6] = NORMAL_ZOMBIE;
    ctx.level.waves[1].types[7] = NORMAL_ZOMBIE;

    // Wave 3
    ctx.level.waves[2].zombieAmmount = 13;

    ctx.level.waves[2].lanes[0] = (u8) random(0, 5);
    ctx.level.waves[2].lanes[1] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[2] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[3] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[4] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[5] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[6] = (u8)random(0, 5);
    ctx.level.waves[2].lanes[7] = 0;
    ctx.level.waves[2].lanes[8] = 1;
    ctx.level.waves[2].lanes[9] = 2;
    ctx.level.waves[2].lanes[10] = 3;
    ctx.level.waves[2].lanes[11] = 4;
    ctx.level.waves[2].lanes[12] = 5;

    ctx.level.waves[2].delays[0] = 150;
    ctx.level.waves[2].delays[1] = 1800;
    ctx.level.waves[2].delays[2] = 1860;
    ctx.level.waves[2].delays[3] = 2700;
    ctx.level.waves[2].delays[4] = 3660;
    ctx.level.waves[2].delays[5] = 3720;
    ctx.level.waves[2].delays[6] = 3780;
    ctx.level.waves[2].delays[7] = 4600;
    ctx.level.waves[2].delays[8] = 4600;
    ctx.level.waves[2].delays[9] = 4600;
    ctx.level.waves[2].delays[10] = 4600;
    ctx.level.waves[2].delays[11] = 4600;
    ctx.level.waves[2].delays[12] = 4600;

    ctx.level.waves[2].types[0] = NORMAL_ZOMBIE;
    ctx.level.waves[2].types[1] = BUCKET_ZOMBIE;
    ctx.level.waves[2].types[2] = NORMAL_ZOMBIE;
    ctx.level.waves[2].types[3] = CONE_ZOMBIE;
    ctx.level.waves[2].types[4] = NORMAL_ZOMBIE;
    ctx.level.waves[2].types[5] = NORMAL_ZOMBIE;
    ctx.level.waves[2].types[6] = CONE_ZOMBIE;
    ctx.level.waves[2].types[7] = BUCKET_ZOMBIE;
    ctx.level.waves[2].types[8] = BUCKET_ZOMBIE;
    ctx.level.waves[2].types[9] = BUCKET_ZOMBIE;
    ctx.level.waves[2].types[10] = BUCKET_ZOMBIE;
    ctx.level.waves[2].types[11] = BUCKET_ZOMBIE;
    ctx.level.waves[2].types[12] = BUCKET_ZOMBIE;
}

void updateTime(Context& ctx){
    ctx.frames += 1;
    ctx.time = (f32)ctx.frames/(f32)FRAMES_PER_SECOND;
}

void updateSun(Context& ctx){
    if(hasTimeElapsed(lastSun, ctx.frames, 0)){
        s16 posX = random(TILE_X_START*TILE_WIDTH, TILE_X_FINAL*TILE_WIDTH);
        s16 posY = random(TILE_Y_START*TILE_HEIGHT, TILE_Y_START*TILE_HEIGHT + SUN_FRAME_WIDTH);
        s16 finalPosY = random((TILE_Y_FINAL-2)*TILE_HEIGHT,TILE_Y_FINAL*TILE_HEIGHT+TILE_HEIGHT/2);
        createSun(ctx, posX, posY, finalPosY);
        lastSun = ctx.frames + random(SUN_MIN_DELAY, SUN_MAX_DELAY) * FRAMES_PER_SECOND;
    }

    for(u8 i = 0; i < MAX_SUN_ON_SCREEN; i++){
        if(ctx.level.suns[i].active){
            if(ctx.level.suns[i].finalPos.y != ctx.level.suns[i].pos.y && ctx.frames % (FRAMES_PER_SECOND/SUN_SPEED) == 0){
                ctx.level.suns[i].pos.y += 1;
            }
        }
    }
}

void updatePlants(Context& ctx){
     for (s8 y = 0; y < TILE_ROWS; y++) {
        for (s8 x = 0; x < TILE_COLUMNS; x++) {
            if(ctx.level.grid[y][x].empty == false){
                PlantEntity* plant = &ctx.level.grid[y][x].plant;
                switch (plant->type){
                case PEASHOOTER:
                    updatePeashooter(ctx, *plant);
                    break;

                case SUNFLOWER:
                    updateSunflower(ctx, *plant);
                    break;
                
                case WALLNUT:
                    updateWallnut(ctx, *plant);
                    break;

                case REPEATER:
                    updateRepeater(ctx, *plant);
                    break;
                
                case POTATOMINE:
                    updatePotatomine(ctx, *plant);
                    break;
                
                default:
                    break;
                }
            }
        }
    }   
}

void updateZombies(Context& ctx){
    for(u8 i = 0; i < MAX_ZOMBIES_PER_WAVE; i++){
        ZombieEntity* zombie = &ctx.level.waves[ctx.level.waveId].zombies[i];

        if(zombie->active && zombie->pos.x < 8){
            ctx.scene = GAME_OVER_SCENE;
        }

        if(zombie->active){
            switch (zombie->type){
            case NORMAL_ZOMBIE:
                updateNormalZombie(ctx, *zombie);
                break;

            case CONE_ZOMBIE:
                updateConeZombie(ctx, *zombie);
                break;

            case BUCKET_ZOMBIE:
                updateBucketZombie(ctx, *zombie);
                break;
            
            default:
                break;
            }
        }
    }
}

void updateWaves(Context& ctx){
    if(ctx.level.waveId+1 > MAX_WAVES){
        if(ctx.currentLevel == MAX_LEVELS){
            ctx.scene = END_SCENE;
        }else{
            ctx.scene = WON_SCENE;
        }
        return;
    }
    for(u8 j = 0; j < MAX_ZOMBIES_PER_WAVE; j++){
        if(ctx.level.waves[ctx.level.waveId].delays[j] <= 0 || ctx.frames > ctx.level.waves[ctx.level.waveId].delays[j] + waveStartTime) {continue;}
        else if(ctx.frames == ctx.level.waves[ctx.level.waveId].delays[j] + waveStartTime){
            createZombie(ctx, ctx.level.waves[ctx.level.waveId].lanes[j], ctx.level.waves[ctx.level.waveId].types[j]);
        }
    }
}

void updateProjectile(Context& ctx){
    for(u8 i = 0; i < MAX_PROJECTILES; i++){
        if(ctx.level.projectiles[i].active){
            if(ctx.level.projectiles[i].pos.x < 170 && ctx.frames % (FRAMES_PER_SECOND/PEA_SPEED) == 0){
                ctx.level.projectiles[i].pos.x += 1;
            }else if(ctx.level.projectiles[i].pos.x >= 170){
                ctx.level.projectiles[i].active = false;
            }
        }
    }
}

void updateCollisions(Context& ctx){
    for (s8 y = 0; y < TILE_ROWS; y++) {
        for (s8 x = 0; x < TILE_COLUMNS; x++) {
            if(ctx.level.grid[y][x].empty){continue;}
            Tile* tile = &ctx.level.grid[y][x];
            for(u8 i = 0; i < MAX_ZOMBIES_PER_WAVE; i++){
                if(!ctx.level.waves[ctx.level.waveId].zombies[i].active){continue;}
                ZombieEntity* zombie = &ctx.level.waves[ctx.level.waveId].zombies[i];

                if(collisionPlantZombie(tile->plant, *zombie)){
                    if((zombie->lastActive - ctx.frames)%72 == 0){
                        zombieAttack(ctx, *tile, *zombie);
                    }
                }
            }
        }
    }

    for(s8 x = 0; x < MAX_PROJECTILES; x++){
        if(!ctx.level.projectiles[x].active){continue;}
        Projectile* proj = &ctx.level.projectiles[x];
            for(u8 i = 0; i < MAX_ZOMBIES_PER_WAVE; i++){
                if(!ctx.level.waves[ctx.level.waveId].zombies[i].active){continue;}
                ZombieEntity* zombie = &ctx.level.waves[ctx.level.waveId].zombies[i];

                if(collisionZombieProjectile(*zombie, *proj)){
                    zombieDamage(ctx, *zombie, *proj);
                }
            }
    }
}

void nextWave(Context& ctx){
    ctx.level.waveId += 1;
    waveStartTime = ctx.frames;
}

void updateLevel(Context& ctx){
    updateSun(ctx);
    updateProjectile(ctx);
    updatePlants(ctx);
    updateZombies(ctx);
    updateWaves(ctx);
    updateCollisions(ctx);
}
