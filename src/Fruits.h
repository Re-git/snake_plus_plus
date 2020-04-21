#ifndef FRUITS_H
#define FRUITS_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"
#include "timer.h"
#include "snake.h"
#include "pig.h"


class Fruit {
public:
    Texture2D sprite;
    Area spawnArea;
    float fruitSize;
    float growing;
    Timer* respawnTimer;
    Rectangle collisionMask;
    Vector2 position;
    Fruit(Texture2D fruitSprite ,Area gameArea);
    ~Fruit();
    void moveFruit();
    void draw(Snake& snake, std::vector<Pig>& pigList, int& points);
    void pulse(float, float);
};


#endif
