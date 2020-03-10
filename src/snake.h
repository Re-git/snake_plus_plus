#ifndef __SNAKE_H_INCLUDED__
#define __SNAKE_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <vector>


class Snake
{
public:
    Vector2 position = {100, 100};
    Vector2 velocity = {0, 0};
    std::vector<Vector2> tail;

    Snake(int length);

    void update();
    void draw();
    bool checkCollisionWithEdges(Vector2 &v);
    void limit(Vector2 &v, float num);
};

#endif