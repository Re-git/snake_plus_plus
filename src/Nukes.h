#ifndef NUKE_H
#define NUKE_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"


class Nukes {
public:
    Texture2D sprite;
    Area spawnArea;
    float nukeSize;
    float growing;
    Rectangle collisionMask;
    Vector2 position;
    Nukes(Texture2D nukeSprite, Area gameArea);
    void moveNuke();
    void draw();
    void update();
    void pulse(float, float);
};


#endif
