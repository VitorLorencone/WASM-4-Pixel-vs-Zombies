#pragma once

#include "utils.h"
#include "constants.h"
#include "types.h"
#include "levels.h"

void initBackgroundEntities(BackgroundEntity* ent);
void createSun(Context& ctx, s16 posX, s16 posY, s16 finalPosY);
void createPlant(Context& ctx, CardEntity& ent, Tile& tile);
void createZombie(Context& ctx, u8 lane, ZombieType type);

void updatePeashooter(Context& ctx, PlantEntity& plant);
void updateSunflower(Context& ctx, PlantEntity& plant);
void updateRepeater(Context& ctx, PlantEntity& plant);
void updateWallnut(Context& ctx, PlantEntity& plant);
void updatePotatomine(Context& ctx, PlantEntity& plant);

void updateNormalZombie(Context& ctx, ZombieEntity& zombie);
void updateConeZombie(Context& ctx, ZombieEntity& zombie);
void updateBucketZombie(Context& ctx, ZombieEntity& zombie);

void peashooterShoot(Context& ctx, PlantEntity& plant);
void potatomineExplode(Context& ctx, Tile& tile, ZombieEntity& zombie);

bool collisionPlantZombie(PlantEntity& plant, ZombieEntity& zombie);
bool collisionZombieProjectile(ZombieEntity& zombie, Projectile& proj);

void zombieAttack(Context& ctx, Tile& tile, ZombieEntity& zombie);
void zombieDamage(Context& ctx, ZombieEntity& zombie, Projectile& proj);

extern CardEntity peashooterCard;
extern CardEntity sunflowerCard;
extern CardEntity repeaterCard;
extern CardEntity wallnutCard;
extern CardEntity potatomineCard;