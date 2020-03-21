
#include "Fruits.h"
Fruits::Fruits(int tMargin,int lMargin, int bMargin) {
    topMargin=tMargin;
    leftMargin=lMargin;
    botMargin=bMargin;
    moveFruit();

}
void Fruits::moveFruit() {

    position.x=((int)std::abs(leftMargin+rand()%(GetScreenWidth()-(leftMargin+FRUIT_SIZE))));
    position.y=((int)std::abs(topMargin+rand()%(GetScreenHeight()-(botMargin+FRUIT_SIZE+topMargin))));
    collisionMask= {position.x,position.y,FRUIT_SIZE,FRUIT_SIZE};
}
void Fruits::draw()
{
    DrawRectangle(position.x, position.y, FRUIT_SIZE,FRUIT_SIZE, BLUE);
}
void Fruits::update() {

}