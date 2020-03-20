#ifndef __SNAKE_H_INCLUDED__
#define __SNAKE_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <vector>


class Snake
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    std::vector<Vector2> tail;
    Snake(int length);

    void update();
    void draw();
    void move();
    bool checkCollisionWithEdges(Vector2&);
    void limit(Vector2&, float);
    bool collide(Rectangle rec);
};

#endif
