#include "BulletTime.h"

Bullet::Bullet(Texture2D BulletTimeSprite[2], Area gameArea) {
    sprite[0] = BulletTimeSprite[0];
    sprite[1] = BulletTimeSprite[1];
    BulletTimeSize = 25;
    spawnArea = gameArea;
    growing = 0.5;
    N = 0;
    podniesiony = false;
    penaltyValue = 0;
    penaltyTimer = new Timer{20000};
    moveBulletTime();
}

Bullet::~Bullet()
{
    delete penaltyTimer;
}

void Bullet::moveBulletTime() {
    position.x=((int)std::abs(spawnArea.left+(int)BulletTimeSize+ rand() % (GetScreenWidth()-spawnArea.right-2*(int)BulletTimeSize)));
    position.y=((int)std::abs(spawnArea.top + rand() % (GetScreenHeight()-spawnArea.bottom-2*(int)BulletTimeSize)));
    collisionMask= {position.x-BulletTimeSize/2,position.y-BulletTimeSize/2,BulletTimeSize,BulletTimeSize};
}
void Bullet::draw(Snake& snake, int& points)
{
  
    if(snake.collide(collisionMask) && podniesiony == false)
    {
        N=1;
        moveBulletTime();
        points-=5;
        SetTargetFPS(30);
        podniesiony = true;       
    }

    if(podniesiony == true)
        if(penaltyTimer->isReady())
        {
        penaltyValue += 10;
        points-=penaltyValue;
        penaltyTimer->reset();
        }


    if(snake.collide(collisionMask) && podniesiony == true)
    {
        N=0;
        moveBulletTime();
        points-=5;
        SetTargetFPS(60);
        podniesiony = false;
    }
    
    pulse(40.0,60.0);
    DrawTexturePro(sprite[N], {0.0f, 0.0f, (float)sprite[N].width, (float)sprite[N].height},
                                     {position.x, position.y, BulletTimeSize, BulletTimeSize},
                                     {BulletTimeSize/2,BulletTimeSize/2},0, WHITE);

}

void Bullet::pulse(float minSize, float maxSize)
{
    BulletTimeSize = BulletTimeSize + growing;
    if (BulletTimeSize < minSize || BulletTimeSize == maxSize)
    {
        growing *= -1;
    }
}