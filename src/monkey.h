#ifndef __MONKEY_H_INCLUDED__
#define __MONKEY_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"


class Malpa
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    int size;

    Malpa();
    void draw();
    void update();
    void move();
    void moveTo(Vector2, float);
    void limit(Vector2&, float);
};

#endif