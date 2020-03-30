#ifndef Explosion_H
#define Explosion_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"


class Explosion {
public:
    Texture2D sprite;
    Area spawnArea;
    float explosionSize;
    float growing;
    Rectangle collisionMask;
    Vector2 position;
    Explosion(Texture2D explosionSprite, Area gameArea);
    void moveExplosion(float posX, float posY);
    void draw();
    void update();
    void pulse(float, float);
};


#endif
    