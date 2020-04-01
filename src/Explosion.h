#ifndef Explosion_H
#define Explosion_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"


class Explosion {
public:
    Texture2D sprites[4];
    float explosionSize;
    int frame;
    int finished;
    Rectangle collisionMask;
    Vector2 position;
    Explosion(Texture2D[4], float, float, size_t);
    void draw();
    void update();

};


#endif
    