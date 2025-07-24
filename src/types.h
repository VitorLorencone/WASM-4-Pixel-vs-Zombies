#pragma once

#include "utils.h"
#include "constants.h"

typedef struct {
    bool animate;
    u16 width, height;
    s16 frameCount;
    u16 frameWidth, frameHeight;
    s16 fps;
    u16 colors;
    const u8* data[];
} Sprite;

typedef enum {
    DEFAULT,
    PEASHOOTER,
    SUNFLOWER,
    WALLNUT,
    REPEATER,
    POTATOMINE
} PlantType;

typedef enum {
    DEF,
    NORMAL_ZOMBIE,
    CONE_ZOMBIE,
    BUCKET_ZOMBIE
} ZombieType;

typedef enum {
    PLANT_DEFAULT,
    PLANT_ATTACKED,

    POTATOMINE_READY,
    SUNFLOWER_SPECIAL
} PlantState;

typedef enum {
    ZOMBIE_DEFAULT,
    ZOMBIE_ATTACKING,
    ZOMBIE_ATTACKED,
    ZOMBIE_ATTACKING_ATTACKED
} ZombieState;

typedef enum {
    PEA,
} ProjectileType;

typedef struct {
    bool active;
    PlantType type;
    Sprite* sprite;
    vec2 pos;

    PlantState state;
    s16 hp;
    s16 damage;
    s16 delay; //frames

    s32 lastActive; //fps

} PlantEntity;

typedef struct {
    bool active;
    ZombieType type;
    Sprite* sprite;
    vec2 pos;

    ZombieState state;
    s16 hp;
    s16 damage;
    s16 delay;
    s16 speed;

    s32 lastActive; //fps

    s16 offset;
    u8 lane;
    
} ZombieEntity;

typedef struct {
    bool active;
    ProjectileType type;
    Sprite* sprite;
    vec2 pos;
} Projectile;

typedef struct {
    vec2 pos;
    s16 speed; // fps
    Sprite* sprite;
} BackgroundEntity;

typedef struct {
    bool active;
    PlantType type;
    Sprite* sprite;
    s16 rechargeTime; //frames
    s16 cost;
    s32 lastActive; //fps
} CardEntity;

typedef struct {
    bool active;
    vec2 pos;
    vec2 finalPos;
} SunEntity;

typedef struct {
    vec2 pos;
    u8 pressedLeftMouse;
    u8 pressedRightMouse;
    u8 pressedXButton;
    CardEntity* selectedPlant;
} Input;

typedef struct Tile{
    vec2 pos;
    bool empty;
    PlantEntity plant;

    Tile(vec2 pos) : pos(pos), empty(true) {};
    Tile() : pos({0, 0}), empty(true) {};
} Tile;

typedef struct{
    s16 zombieAmmount;
    s32 delays[MAX_ZOMBIES_PER_WAVE];
    ZombieEntity zombies[MAX_ZOMBIES_PER_WAVE];
    u8 lanes[MAX_ZOMBIES_PER_WAVE];
    ZombieType types[MAX_ZOMBIES_PER_WAVE];
} Wave;

typedef struct {
    u8 waveId;
    s16 sunAmmount;
    Tile grid[TILE_ROWS][TILE_COLUMNS];
    BackgroundEntity backgroundEntity[BACKGROUND_ENTITIES];
    SunEntity suns[MAX_SUN_ON_SCREEN];
    CardEntity avaliablePlants[MAX_AVALIABLE_PLANTS];
    Wave waves[MAX_WAVES];
    Projectile projectiles[MAX_PROJECTILES];
} Level;

typedef enum{
    START_SCENE,
    LEVEL1_SCENE,
    LEVEL2_SCENE,
    LEVEL3_SCENE,
    END_SCENE,
    GAME_OVER_SCENE,
    WON_SCENE
} Scene;

typedef struct {
    s32 frames;
    f32 time;
    Input input;
    Level level;
    Scene scene;
    u8 currentLevel;
} Context;