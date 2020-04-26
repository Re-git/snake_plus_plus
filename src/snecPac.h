#ifndef SNECPAC_H
#define SNECPAC_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"
#include "timer.h"
#include "snake.h"
#include "pig.h"
#include "Fruits.h"

class SnekPac
{
public:
    Texture2D sprite;
    Area spawnArea;
    float fruitSize;
    float growing;
    bool modeActive;
    Timer* respawnTimer;
    Timer* outsideTimer;
    Rectangle collisionMask;
    Vector2 position;
    SnekPac(Texture2D fruitSprite ,Area gameArea);
    ~SnekPac();
    void moveSnekPac();
    void moveSnekPacOutside();
    void draw(Snake& snake, int& points);
    void pulse(float, float);
};

#endif