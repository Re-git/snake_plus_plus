
#include "Nukes.h"


Nuke::Nuke(Texture2D nukesSprite, Area gameArea){
    sprite = nukesSprite;
    nukeSize = 45;
    spawnArea = gameArea;
    respawnTimer = new Timer(10000);
    growing = 0.5;
    moveNuke();
}

Nuke::~Nuke()
{
    delete respawnTimer;
}

void Nuke::moveNuke(){

    position.x = ((int)std::abs(spawnArea.left + (int)nukeSize + rand() % (GetScreenWidth() - spawnArea.right - 2 * (int)nukeSize)));
    position.y = ((int)std::abs(spawnArea.top + rand() % (GetScreenHeight() - spawnArea.bottom - 2 * (int)nukeSize)));
    collisionMask = { position.x - nukeSize / 2,position.y - nukeSize / 2,nukeSize,nukeSize };
}
void Nuke::draw(){
    if (respawnTimer->isReady())
    {
    moveNuke();
    respawnTimer->reset();
    }



    pulse(40.0, 60.0);
    DrawTexturePro(sprite, { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height },
        { position.x, position.y, nukeSize, nukeSize },
        { nukeSize / 2,nukeSize / 2 }, 0, WHITE);
}

void Nuke::pulse(float minSize, float maxSize){
    nukeSize = nukeSize + growing;
    if (nukeSize < minSize || nukeSize == maxSize)
    {
        growing *= -1;
    }
}