#include "Fruits.h"

Fruit::Fruit(Texture2D fruitSprite, Area gameArea) {
    respawnTimer = new Timer{10000};
    sprite = fruitSprite;
    fruitSize = 45;
    spawnArea = gameArea;
    growing = 0.5;
    moveFruit();
}

Fruit::~Fruit()
{
    delete respawnTimer;
}

void Fruit::moveFruit() {

    position.x=((int)std::abs(spawnArea.left+(int)fruitSize+ rand() % (GetScreenWidth()-spawnArea.right-2*(int)fruitSize)));
    position.y=((int)std::abs(spawnArea.top + rand() % (GetScreenHeight()-spawnArea.bottom-2*(int)fruitSize)));
    collisionMask= {position.x-fruitSize/2,position.y-fruitSize/2,fruitSize,fruitSize};
}
void Fruit::draw(Snake& snake, std::vector<Pig>& pigList,  int& points, Sound Eat)
{
    if(snake.collide(collisionMask))
        {
            points+=10;
            moveFruit();
            respawnTimer->reset();
            PlaySoundMulti(Eat);

            for (size_t i = 0; i < 2; i++)
            {
                snake.tail.push_back(Vector2{snake.position.x, snake.position.y});
            }                
        }
    if (!pigList.empty()) {
        if (pigList[0].collide(collisionMask)) {
            pigList[0].iloscZjedzonych+=5;
            points-=5;
            moveFruit();
            respawnTimer->reset();
        }
    }
    
    if(respawnTimer->isReady())
        {
            moveFruit();
            respawnTimer->reset();
        }
    pulse(40.0,60.0);
    DrawTexturePro(sprite, {0.0f, 0.0f, (float)sprite.width, (float)sprite.height},
                                     {position.x, position.y, fruitSize, fruitSize},
                                     {fruitSize/2,fruitSize/2},0, WHITE);
}

void Fruit::pulse(float minSize, float maxSize)
{
    fruitSize = fruitSize + growing;
    if (fruitSize < minSize || fruitSize == maxSize)
    {
        growing *= -1;
    }
}
