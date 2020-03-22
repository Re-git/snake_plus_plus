
#include "Fruits.h"
Fruits::Fruits(int tMargin,int lMargin, int bMargin) {
    sprite = LoadTexture("assets/sprites/owocek.png");
    fruitSize = 45;
    topMargin=tMargin;
    leftMargin=lMargin;
    botMargin=bMargin;
    growing = 0.5;
    moveFruit();

}
void Fruits::moveFruit() {

    position.x=((int)std::abs(leftMargin+rand()%(GetScreenWidth()-(leftMargin+(int)fruitSize))));
    position.y=((int)std::abs(topMargin+rand()%(GetScreenHeight()-(botMargin+(int)fruitSize+topMargin))));
    collisionMask= {position.x-fruitSize/2,position.y-fruitSize/2,fruitSize,fruitSize};
}
void Fruits::draw()
{
    fruitSize = fruitSize + growing;
    if (fruitSize < 40 || fruitSize == 60)
    {
        growing *= -1;
    }

    DrawTexturePro(sprite, {0.0f, 0.0f, (float)sprite.width, (float)sprite.height},
                                     {position.x, position.y, fruitSize, fruitSize},
                                     {fruitSize/2,fruitSize/2},0, WHITE);
   
    
    
    
}
void Fruits::update() {

}