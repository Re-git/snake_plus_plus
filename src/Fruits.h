#ifndef FRUITS_H
#define FRUITS_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>

const int FRUIT_SIZE=25;

class Fruits {
public:
    int topMargin;
    int leftMargin;
    int botMargin;
    Rectangle collisionMask;
    Vector2 position;
    Fruits(int topMargin,int leftMargin, int botMargin);
    void moveFruit();
    void draw();
    void update();


};


#endif
