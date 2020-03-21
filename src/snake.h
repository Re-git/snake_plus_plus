#ifndef __SNAKE_H_INCLUDED__
#define __SNAKE_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <vector>
#include <iostream>

class Snake
{
public:
    Vector2 position;
    Vector2 velocity;
    float maxSpeed;
    float angle;
    float turnRate;
    std::vector<Vector2> tail;
    Snake(int length);

    void update();
    void draw();
    void move();
    void handleInput();
    bool checkCollisionWithEdges(Vector2&);
    void limit(Vector2&, float);
    bool collide(Rectangle rec);
    void turn(float);
};

#endif
