#ifndef BULLETTIME_H
#define BULLETTIME_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>
#include "utility.h"
#include "timer.h"
#include "snake.h"


class Bullet {
public:
    Texture2D sprite[2];
    Area spawnArea;
    float BulletTimeSize;
    float growing;
    Timer* penaltyTimer;
    Timer* outsideTimer;
    int penaltyValue;
    Rectangle collisionMask;
    Vector2 position;
    bool podniesiony, outside;
    int N;
    Bullet(Texture2D BulletTimeSprite[2] ,Area gameArea);
    ~Bullet();
    void moveBulletTime();
    void moveBulletTimeOutside();
    void draw(Snake& snake, int& points);
    void pulse(float, float);
};


#endif
