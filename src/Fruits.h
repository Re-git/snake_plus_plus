#ifndef FRUITS_H
#define FRUITS_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>



class Fruits {
public:
    Texture2D sprite;
    Rectangle spawnArea;
    float fruitSize;
    float growing;
    Rectangle collisionMask;
    Vector2 position;
    Fruits(Texture2D fruitSprite ,Rectangle gameArea);
    void moveFruit();
    void draw();
    void update();
    void pulse(float, float);
};


#endif
