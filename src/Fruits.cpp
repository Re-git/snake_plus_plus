
#include "Fruits.h"
Fruits::Fruits() {
    moveFruit();
}
void Fruits::moveFruit() {
    position.x=((int)std::abs(rand()%(800-FRUIT_SIZE)));
    position.y=((int)std::abs(rand()%(800-FRUIT_SIZE)));
    collisionMask= {position.x,position.y,FRUIT_SIZE,FRUIT_SIZE};
}
void Fruits::draw()
{
    DrawRectangle(position.x, position.y, FRUIT_SIZE,FRUIT_SIZE, BLUE);
}
void Fruits::update() {

}