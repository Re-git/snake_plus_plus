#ifndef SNAKE_PLUS_PLUS_FROSTNUKE_H
#define SNAKE_PLUS_PLUS_FROSTNUKE_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"
#include "timer.h"
#include "snake.h"
#include "monkey.h"
#include "FrostExplosion.h"


class FrostNuke {
public:
    Texture2D sprite;
    Area spawnArea;
    float frostNukeSize;
    float growing;
    bool outside;
    Timer* respawnTimer;
    Timer* outsideTimer;
    Rectangle collisionMask;
    Vector2 position;
    FrostNuke(Texture2D frostNukeSprite, Area gameArea);
    ~FrostNuke();
    void moveFrostNuke();
    void moveFrostNukeOutside();
    void draw();
    void pulse(float, float);
};



#endif
