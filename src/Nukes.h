#ifndef NUKE_H
#define NUKE_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"
#include "timer.h"
#include "snake.h"
#include "monkey.h"
#include "Explosion.h"


class Nuke {
public:
    Texture2D sprite;
    Area spawnArea;
    float nukeSize;
    float growing;
    Timer* respawnTimer;
    Rectangle collisionMask;
    Vector2 position;
    Nuke(Texture2D nukeSprite, Area gameArea);
    ~Nuke();
    void moveNuke();
    void draw();
    void pulse(float, float);
};


#endif
