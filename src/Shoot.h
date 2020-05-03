#ifndef __SHOOT_H_INCLUDED__
#define __SHOOT_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"
#include "timer.h"
#include <vector>



class Shoot {
public:
    Vector2 speed;
    Texture2D sprite;
    bool active;
    Vector2 position;
    int lifeSpawn;
    float radius;
    Shoot(Texture2D kissSprite);
};

#endif