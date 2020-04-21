#ifndef SNAKE_PLUS_PLUS_FROSTEXPLOSION_H
#define SNAKE_PLUS_PLUS_FROSTEXPLOSION_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"

class FrostExplosion {
public:
    Texture2D sprites[5];
    float frostExplosionSize;
    int frame;
    int finished;
    Rectangle collisionMask;
    Vector2 position;
    FrostExplosion(Texture2D[4], float, float, size_t);
    void draw();
    void update();

};


#endif