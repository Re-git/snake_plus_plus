#ifndef FRUITS_H
#define FRUITS_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>

const int FRUIT_SIZE=25;

class Fruits {
public:
    Rectangle collisionMask;
    Vector2 position;
    Fruits();
    void moveFruit();
    void draw();
    void update();


};


#endif
