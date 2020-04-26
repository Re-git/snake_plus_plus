#include "snecPac.h"


SnekPac::SnekPac(Texture2D fruitSprite, Area gameArea) {
    sprite = fruitSprite;
    fruitSize = 45;
    spawnArea = gameArea;
    respawnTimer = new Timer(10000);
    outsideTimer = new Timer(30000);
    growing = 0.5;
    modeActive = 0;
    moveSnekPac();
}

SnekPac::~SnekPac()
{
    delete respawnTimer;
    delete outsideTimer;
}

void SnekPac::moveSnekPac() {

    position.x=((int)std::abs(spawnArea.left+(int)fruitSize+ rand() % (GetScreenWidth()-spawnArea.right-2*(int)fruitSize)));
    position.y=((int)std::abs(spawnArea.top + rand() % (GetScreenHeight()-spawnArea.bottom-2*(int)fruitSize)));
    collisionMask= {position.x-fruitSize/2,position.y-fruitSize/2,fruitSize,fruitSize};
}

void SnekPac::moveSnekPacOutside() {
    position.x=-100;
    position.y=-100;
    collisionMask= {position.x-fruitSize/2,position.y-fruitSize/2,fruitSize,fruitSize};
    outsideTimer -> reset();
    respawnTimer -> reset();
}

void SnekPac::draw(Snake& snake,  int& points)
{
    
    if (outsideTimer -> isReady())
    {
        moveSnekPac();
        outsideTimer -> reset();
    }


    if(modeActive==true)
    {
        snake.snekPacMode = 1;

        if(respawnTimer->getTime()>7999ul)
        {
            snake.dangerMode = 1;
        }

        if(respawnTimer->isReady())
        {
            modeActive = 0;
            // moveSnekPac();
            snake.snekPacMode = 0;
            snake.dangerMode = 0;
            respawnTimer->reset();
        }
    }

    pulse(40.0,60.0);
    DrawTexturePro(sprite, {0.0f, 0.0f, (float)sprite.width, (float)sprite.height},
                                     {position.x, position.y, fruitSize, fruitSize},
                                     {fruitSize/2,fruitSize/2},0, WHITE);
}

void SnekPac::pulse(float minSize, float maxSize)
{
    fruitSize = fruitSize + growing;
    if (fruitSize < minSize || fruitSize == maxSize)
    {
        growing *= -1;
    }
}
