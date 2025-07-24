#include "entities.h"
#include "sprite.h"
#include "wasm4.h"

CardEntity peashooterCard = {true, PEASHOOTER, &peashooterSprite, PEASHOOTER_RECHARGE, PEASHOOTER_COST, 0};
CardEntity sunflowerCard = {true, SUNFLOWER, &sunflowerSprite, SUNFLOWER_RECHARGE, SUNFLOWER_COST, 0};
CardEntity repeaterCard = {true, REPEATER, &repeaterSprite, REPEATER_RECHARGE, REPEATER_COST, 0};
CardEntity wallnutCard = {true, WALLNUT, &wallnutSprite, WALLNUT_RECHARGE, WALLNUT_COST, 0};
CardEntity potatomineCard = {true, POTATOMINE, &potatomineReadySprite, POTATOMINE_RECHARGE, POTATOMINE_COST, 0};

void initBackgroundEntities(BackgroundEntity* ent) {
    ent[0] = {BIRD_1_START_POSITION, BIRD_SPEED, &birdSprite};
    ent[1] = {BIRD_2_START_POSITION, BIRD_SPEED, &birdSprite};
    ent[2] = {CLOUD1_START_POSITION, CLOUD1_SPEED, &cloud1Sprite};
    ent[3] = {CLOUD2_START_POSITION, CLOUD2_SPEED, &cloud2Sprite};
    ent[4] = {CLOUD3_START_POSITION, CLOUD3_SPEED, &cloud3Sprite};
    ent[5] = {CLOUD4_START_POSITION, CLOUD4_SPEED, &cloud4Sprite};
}

bool zombieOnLane(Context& ctx, u8 lane){
    for(u8 i = 0; i < MAX_ZOMBIES_PER_WAVE; i++){
        ZombieEntity* zombie = &ctx.level.waves[ctx.level.waveId].zombies[i];
        if(zombie->active && zombie->lane == lane){
            return true;
        }
    }
    return false;
}

void createSun(Context& ctx, s16 posX, s16 posY, s16 finalPosY){
    for(u8 i = 0; i < MAX_SUN_ON_SCREEN; i++){
        if(!ctx.level.suns[i].active){
            ctx.level.suns[i].active = true;
            ctx.level.suns[i].pos = vec2(posX, posY);
            ctx.level.suns[i].finalPos = vec2(posX, finalPosY);
            return;
        }
    }
}

void createPlant(Context& ctx, CardEntity& ent, Tile& tile){

    if(ctx.level.sunAmmount < ent.cost){return;}

    PlantEntity plant;
    switch (ent.type){

    case PEASHOOTER:
        plant.active = true;
        plant.type = PEASHOOTER;
        plant.damage = PEASHOOTER_DAMAGE;
        plant.delay = PEASHOOTER_DELAY;
        plant.hp = PEASHOOTER_HP;
        plant.sprite = &peashooterSprite;
        plant.lastActive = ctx.frames + plant.delay;
        plant.pos.x = tile.pos.x * TILE_WIDTH + TILE_X_START*TILE_WIDTH;
        plant.pos.y = tile.pos.y * TILE_HEIGHT + TILE_Y_START*TILE_HEIGHT;
        break;
    
    case SUNFLOWER:
        plant.active = true;
        plant.type = SUNFLOWER;
        plant.damage = SUNFLOWER_DAMAGE;
        plant.delay = SUNFLOWER_DELAY;
        plant.hp = SUNFLOWER_HP;
        plant.sprite = &sunflowerSprite;
        plant.lastActive = ctx.frames + plant.delay;
        plant.pos.x = tile.pos.x * TILE_WIDTH + TILE_X_START*TILE_WIDTH;
        plant.pos.y = tile.pos.y * TILE_HEIGHT + TILE_Y_START*TILE_HEIGHT;
        break;

    case REPEATER:
        plant.active = true;
        plant.type = REPEATER;
        plant.damage = REPEATER_DAMAGE;
        plant.delay = REPEATER_DELAY;
        plant.hp = REPEATER_HP;
        plant.sprite = &repeaterSprite;
        plant.lastActive = ctx.frames + plant.delay;
        plant.pos.x = tile.pos.x * TILE_WIDTH + TILE_X_START*TILE_WIDTH;
        plant.pos.y = tile.pos.y * TILE_HEIGHT + TILE_Y_START*TILE_HEIGHT;
        break;
    
    case WALLNUT:
        plant.active = true;
        plant.type = WALLNUT;
        plant.damage = WALLNUT_DAMAGE;
        plant.delay = WALLNUT_DELAY;
        plant.hp = WALLNUT_HP;
        plant.sprite = &wallnutSprite;
        plant.pos.x = tile.pos.x * TILE_WIDTH + TILE_X_START*TILE_WIDTH;
        plant.pos.y = tile.pos.y * TILE_HEIGHT + TILE_Y_START*TILE_HEIGHT;
        break;

    case POTATOMINE:
        plant.active = true;
        plant.state = PLANT_DEFAULT;
        plant.type = POTATOMINE;
        plant.damage = POTATOMINE_SLEEP_DAMAGE;
        plant.delay = POTATOMINE_DELAY;
        plant.hp = POTATOMINE_SLEEP_HP;
        plant.sprite = &potatomineSleepSprite;
        plant.lastActive = ctx.frames + plant.delay;
        plant.pos.x = tile.pos.x * TILE_WIDTH + TILE_X_START*TILE_WIDTH;
        plant.pos.y = tile.pos.y * TILE_HEIGHT + TILE_Y_START*TILE_HEIGHT;
        break;

    default:
        break;
    }

    ent.lastActive = ctx.frames + ent.rechargeTime;
    ctx.level.sunAmmount -= ent.cost;
    tile.empty = false;
    tile.plant = plant;

    ctx.input.selectedPlant = nullptr;
}

void createZombie(Context& ctx, u8 lane, ZombieType type){
    ZombieEntity zombie;

    switch (type){
    case NORMAL_ZOMBIE:
        zombie.active = true;
        zombie.state = ZOMBIE_DEFAULT;
        zombie.type = type;
        zombie.damage = ZOMBIE_DAMAGE;
        zombie.delay = ZOMBIE_DELAY;
        zombie.hp = ZOMBIE_HP;
        zombie.speed = ZOMBIE_SPEED;
        zombie.sprite = &zombieSprite;
        zombie.lastActive = ctx.frames + zombie.delay;
        zombie.offset = NORMAL_ZOMBIE_OFFSET;
        zombie.lane = lane;
        zombie.pos.x = 160;
        zombie.pos.y = TILE_Y_START*TILE_HEIGHT + lane * TILE_HEIGHT - NORMAL_ZOMBIE_OFFSET;
        break;
    
    case CONE_ZOMBIE:
        zombie.active = true;
        zombie.state = ZOMBIE_DEFAULT;
        zombie.type = type;
        zombie.damage = CONE_ZOMBIE_DAMAGE;
        zombie.delay = CONE_ZOMBIE_DELAY;
        zombie.hp = CONE_ZOMBIE_HP;
        zombie.speed = CONE_ZOMBIE_SPEED;
        zombie.sprite = &coneZombieSprite;
        zombie.lastActive = ctx.frames + zombie.delay;
        zombie.offset = CONE_ZOMBIE_OFFSET;
        zombie.lane = lane;
        zombie.pos.x = 160;
        zombie.pos.y = TILE_Y_START*TILE_HEIGHT + lane * TILE_HEIGHT - CONE_ZOMBIE_OFFSET;
        break;

    case BUCKET_ZOMBIE:
        zombie.active = true;
        zombie.state = ZOMBIE_DEFAULT;
        zombie.type = type;
        zombie.damage = BUCKET_ZOMBIE_DAMAGE;
        zombie.delay = BUCKET_ZOMBIE_DELAY;
        zombie.hp = BUCKET_ZOMBIE_HP;
        zombie.speed = BUCKET_ZOMBIE_SPEED;
        zombie.sprite = &bucketZombieSprite;
        zombie.lastActive = ctx.frames + zombie.delay;
        zombie.offset = BUCKET_ZOMBIE_OFFSET;
        zombie.lane = lane;
        zombie.pos.x = 160;
        zombie.pos.y = TILE_Y_START*TILE_HEIGHT + lane * TILE_HEIGHT - BUCKET_ZOMBIE_OFFSET;
    
    default:
        break;
    }

    for(u8 i = 0; i < MAX_ZOMBIES_PER_WAVE; i++){
        if(!ctx.level.waves[ctx.level.waveId].zombies[i].active){
            ctx.level.waves[ctx.level.waveId].zombies[i] = zombie;
            break;
        }
    }
}

void peashooterShoot(Context& ctx, PlantEntity& plant){
    for(u8 i = 0; i < MAX_PROJECTILES; i++){
        if(!ctx.level.projectiles[i].active){
            ctx.level.projectiles[i].active = true;
            ctx.level.projectiles[i].type = PEA;
            ctx.level.projectiles[i].pos.x = plant.pos.x+13;
            ctx.level.projectiles[i].pos.y = plant.pos.y+4;
            ctx.level.projectiles[i].sprite = &peaSprite;
            return;
        }
    }
}

void updatePeashooter(Context& ctx, PlantEntity& plant){
    
    if(plant.state == PLANT_ATTACKED && (plant.lastActive - ctx.frames) % 5 == 0){
        plant.state = PLANT_DEFAULT;
    }
    
    if(zombieOnLane(ctx, (u8)(plant.pos.y - TILE_Y_START*TILE_HEIGHT)/TILE_HEIGHT)){
        if(plant.lastActive - ctx.frames > 0){
            return;
        }else{
            peashooterShoot(ctx, plant);
            plant.lastActive = ctx.frames + plant.delay;
        }
    }
}

void updateSunflower(Context& ctx, PlantEntity& plant){
    
    if(plant.state == PLANT_ATTACKED && (plant.lastActive - ctx.frames) % 5 == 0){
        plant.state = PLANT_DEFAULT;
    }
    
    if(plant.lastActive - ctx.frames > 0){
        if(plant.state != PLANT_ATTACKED && plant.lastActive - ctx.frames < FRAMES_PER_SECOND*3){
            plant.state = SUNFLOWER_SPECIAL;
        }
    }else{
        s16 posX = random((u32)plant.pos.x-5, (u32)plant.pos.x+5);
        s16 posY = random((u32)plant.pos.y, (u32)plant.pos.y+3);
        s16 finalPosY = posY+5;
        createSun(ctx, posX, posY, finalPosY);

        plant.lastActive = ctx.frames + plant.delay;
        plant.state = PLANT_DEFAULT;
    }
}

void updateRepeater(Context& ctx, PlantEntity& plant){
    if(plant.state == PLANT_ATTACKED && (plant.lastActive - ctx.frames) % 5 == 0){
        plant.state = PLANT_DEFAULT;
    }
    
    if(zombieOnLane(ctx, (u8)(plant.pos.y - TILE_Y_START*TILE_HEIGHT)/TILE_HEIGHT)){
        if(plant.lastActive - ctx.frames > 0){
            return;
        }else{
            if(plant.lastActive - ctx.frames > -FRAMES_PER_SECOND/3){
                peashooterShoot(ctx, plant);
                plant.lastActive = ctx.frames -FRAMES_PER_SECOND/3;
            }else if(plant.lastActive - ctx.frames < -FRAMES_PER_SECOND/2){
                peashooterShoot(ctx, plant);
                plant.lastActive = ctx.frames + plant.delay;
            }
        }
    }
}

void updateWallnut(Context& ctx, PlantEntity& plant){
    if(plant.state == PLANT_ATTACKED && ctx.frames % 5 == 0){
        plant.state = PLANT_DEFAULT;
    }
}

void updatePotatomine(Context& ctx, PlantEntity& plant){
        
    if(plant.state == PLANT_ATTACKED && (plant.lastActive - ctx.frames) % 5 == 0){
        plant.state = PLANT_DEFAULT;
    }

    if(plant.state == POTATOMINE_READY){
        plant.sprite = &potatomineReadySprite;
    }else{
        plant.sprite = &potatomineSleepSprite;
    }
    
    if(plant.lastActive - ctx.frames > 0){
        return;
    }else{
        plant.state = POTATOMINE_READY;
        plant.lastActive = ctx.frames + plant.delay;
    }
}

void updateNormalZombie(Context& ctx, ZombieEntity& zombie){
    if(zombie.state == ZOMBIE_DEFAULT){
        zombie.sprite = &zombieSprite;
    }else if(zombie.state == ZOMBIE_ATTACKING || zombie.state == ZOMBIE_ATTACKING_ATTACKED){
        zombie.sprite = &zombieAttackingSprite;
    }

    if((zombie.state == ZOMBIE_ATTACKED || zombie.state == ZOMBIE_ATTACKING_ATTACKED) && (zombie.lastActive - ctx.frames) % 5 == 0){
        if(zombie.state == ZOMBIE_ATTACKED){
            zombie.state = ZOMBIE_DEFAULT;
        }else{
            zombie.state = ZOMBIE_ATTACKING;
        }
    }

    if(zombie.state != ZOMBIE_ATTACKING && zombie.state != ZOMBIE_ATTACKING_ATTACKED){
        if(zombie.lastActive - ctx.frames > 0){
            return;
        }else{
            if(zombie.lastActive - ctx.frames > -FRAMES_PER_SECOND){
                if(ctx.frames % (FRAMES_PER_SECOND/zombie.speed) == 0){
                    zombie.pos.x -= 1;
                }
            }else{
                zombie.lastActive = ctx.frames + zombie.delay;
            }
        }
    }
}

void updateConeZombie(Context& ctx, ZombieEntity& zombie){
    if(zombie.state == ZOMBIE_DEFAULT){
        zombie.sprite = &coneZombieSprite;
    }else if(zombie.state == ZOMBIE_ATTACKING || zombie.state == ZOMBIE_ATTACKING_ATTACKED){
        zombie.sprite = &coneZombieAttackingSprite;
    }

    if((zombie.state == ZOMBIE_ATTACKED || zombie.state == ZOMBIE_ATTACKING_ATTACKED) && (zombie.lastActive - ctx.frames) % 5 == 0){
        if(zombie.state == ZOMBIE_ATTACKED){
            zombie.state = ZOMBIE_DEFAULT;
        }else{
            zombie.state = ZOMBIE_ATTACKING;
        }
    }

    if(zombie.state != ZOMBIE_ATTACKING && zombie.state != ZOMBIE_ATTACKING_ATTACKED){
        if(zombie.lastActive - ctx.frames > 0){
            return;
        }else{
            if(zombie.lastActive - ctx.frames > -FRAMES_PER_SECOND){
                if(ctx.frames % (FRAMES_PER_SECOND/zombie.speed) == 0){
                    zombie.pos.x -= 1;
                }
            }else{
                zombie.lastActive = ctx.frames + zombie.delay;
            }
        }
    }
}

void updateBucketZombie(Context& ctx, ZombieEntity& zombie){
    if(zombie.state == ZOMBIE_DEFAULT){
        zombie.sprite = &bucketZombieSprite;
    }else if(zombie.state == ZOMBIE_ATTACKING || zombie.state == ZOMBIE_ATTACKING_ATTACKED){
        zombie.sprite = &bucketZombieAttackingSprite;
    }

    if((zombie.state == ZOMBIE_ATTACKED || zombie.state == ZOMBIE_ATTACKING_ATTACKED) && (zombie.lastActive - ctx.frames) % 5 == 0){
        if(zombie.state == ZOMBIE_ATTACKED){
            zombie.state = ZOMBIE_DEFAULT;
        }else{
            zombie.state = ZOMBIE_ATTACKING;
        }
    }

    if(zombie.state != ZOMBIE_ATTACKING && zombie.state != ZOMBIE_ATTACKING_ATTACKED){
        if(zombie.lastActive - ctx.frames > 0){
            return;
        }else{
            if(zombie.lastActive - ctx.frames > -FRAMES_PER_SECOND){
                if(ctx.frames % (FRAMES_PER_SECOND/zombie.speed) == 0){
                    zombie.pos.x -= 1;
                }
            }else{
                zombie.lastActive = ctx.frames + zombie.delay;
            }
        }
    }
}

bool collisionPlantZombie(PlantEntity& plant, ZombieEntity& zombie) {
    return plant.pos.x < zombie.pos.x + zombie.sprite->frameWidth &&
           plant.pos.x + plant.sprite->frameWidth > zombie.pos.x+3 &&
           plant.pos.y < zombie.pos.y + 16 + zombie.offset-2 &&
           plant.pos.y + plant.sprite->frameHeight > zombie.pos.y + zombie.offset+2;
}

bool collisionZombieProjectile(ZombieEntity& zombie, Projectile& proj) {
    return proj.pos.x < zombie.pos.x + zombie.sprite->frameWidth &&
           proj.pos.x + proj.sprite->frameWidth > zombie.pos.x+3 &&
           proj.pos.y < zombie.pos.y + 16 + zombie.offset-2 &&
           proj.pos.y + proj.sprite->frameHeight > zombie.pos.y + zombie.offset+2;
}

void zombieSubHP(Context& ctx, ZombieEntity& zombie, u8 hp){
    zombie.hp -= hp;
    if(zombie.hp <= 0){
        zombie.active = false;
        zombie.state = ZOMBIE_DEFAULT;
        ctx.level.waves[ctx.level.waveId].zombieAmmount -= 1;
        if(ctx.level.waves[ctx.level.waveId].zombieAmmount <= 0){
            nextWave(ctx);
        }
    }
}

void plantSubHP(Tile& tile, u8 hp){
    tile.plant.hp -= hp;
    if(tile.plant.hp <= 0){
        tile.plant.active = false;
        tile.empty = true;
    }
}

void potatomineExplode(Context& ctx, Tile& tile, ZombieEntity& zombie){
    plantSubHP(tile, 100);
    zombieSubHP(ctx, zombie, POTATOMINE_READY_DAMAGE);
}

void zombieAttack(Context& ctx, Tile& tile, ZombieEntity& zombie){
    if(tile.plant.type == POTATOMINE && tile.plant.state == POTATOMINE_READY){
        potatomineExplode(ctx, tile, zombie);
    }

    if(zombie.state == ZOMBIE_ATTACKED){
        zombie.state = ZOMBIE_ATTACKING_ATTACKED;
    }else{
        zombie.state = ZOMBIE_ATTACKING;
    }

    tile.plant.state = PLANT_ATTACKED;
    plantSubHP(tile, (u8)zombie.damage);
    if(tile.empty || tile.plant.active == false){
        zombie.state = ZOMBIE_DEFAULT;
    }
}

void zombieDamage(Context& ctx, ZombieEntity& zombie, Projectile& proj){
    if(zombie.state == ZOMBIE_ATTACKING){
        zombie.state = ZOMBIE_ATTACKING_ATTACKED;
    }else{
        zombie.state = ZOMBIE_ATTACKED;
    }
    switch(proj.type){
    case PEA:
        zombieSubHP(ctx, zombie, 1);
        break;
    
    default:
        break;
    }

    proj.active = false;
}