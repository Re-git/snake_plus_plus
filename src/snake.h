#ifndef __SNAKE_H_INCLUDED__
#define __SNAKE_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <vector>
#include <iostream>

class Snake
{
public:
    Texture2D sprite;
    float headHeight;
    float headWidth;
    float bodyHeight;
    float bodyWidth;
    Vector2 position;
    Vector2 velocity;
    float maxSpeed;
    float angle;
    float turnRate;
    float speedModifier;
    std::vector<Vector2> tail;
    Snake(Texture2D snakeSprite ,int length);

    void update();
    void draw();
    void move();
    void handleInput();
    bool checkCollisionWithEdges(Vector2&);
    void limit(Vector2&, float);
    bool collide(Rectangle rec);
    void turn(float);
    void limitAngle(float);
};

#endif
