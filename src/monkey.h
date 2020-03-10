#ifndef __MONKEY_H_INCLUDED__
#define __MONKEY_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"


class Malpa
{
public:
    Vector2 position = {100, 100};
    Vector2 velocity = {0, 0};
    int size;

    Malpa();
    void draw();
    void update();
};

#endif