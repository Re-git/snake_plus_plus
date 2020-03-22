
#include "Fruits.h"

Fruits::Fruits(Texture2D fruitSprite, Rectangle gameArea) {
    sprite = fruitSprite;
    fruitSize = 45;
    spawnArea = gameArea;
    growing = 0.5;
    moveFruit();
}

void Fruits::moveFruit() {

    position.x=((int)std::abs(rand() % ((int)spawnArea.width)+(GetScreenWidth()-spawnArea.width)));
    position.y=((int)std::abs(rand()% (int)(spawnArea.height - 2*fruitSize)+(GetScreenHeight()-spawnArea.height+(int)fruitSize)));
    collisionMask= {position.x-fruitSize/2,position.y-fruitSize/2,fruitSize,fruitSize};
}
void Fruits::draw()
{

    DrawTexturePro(sprite, {0.0f, 0.0f, (float)sprite.width, (float)sprite.height},
                                     {position.x, position.y, fruitSize, fruitSize},
                                     {fruitSize/2,fruitSize/2},0, WHITE);
}

void Fruits::update() {
    pulse(40.0,60.0);
}

void Fruits::pulse(float minSize, float maxSize)
{
    fruitSize = fruitSize + growing;
    if (fruitSize < minSize || fruitSize == maxSize)
    {
        growing *= -1;
    }
}