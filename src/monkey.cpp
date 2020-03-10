#include "monkey.h"


Malpa::Malpa()
{
    position.x = rand() % GetScreenWidth();
    position.y = rand() % GetScreenHeight();
    size = rand() % 100;
}


void Malpa::draw()
{
    DrawText("@", position.x, position.y, size, BROWN);
}


void Malpa::update()
{
    // tutaj jakieś ruchy małpie trzeba dodać
}
