#ifndef FRUITS_H
#define FRUITS_H

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "stdlib.h"
#include <vector>



class Fruits {
public:
    Texture2D sprite;  
    float fruitSize;
    int topMargin;
    int leftMargin;
    int botMargin;
    float growing;
    Rectangle collisionMask;
    Vector2 position;
    Fruits(int topMargin,int leftMargin, int botMargin);
    void moveFruit();
    void draw();
    void update();


};


#endif
