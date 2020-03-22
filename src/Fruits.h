#ifndef FRUITS_H
#define FRUITS_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"


class Fruits {
public:
    Texture2D sprite;
    Area spawnArea;
    float fruitSize;
    float growing;
    Rectangle collisionMask;
    Vector2 position;
    Fruits(Texture2D fruitSprite ,Area gameArea);
    void moveFruit();
    void draw();
    void update();
    void pulse(float, float);
};


#endif
