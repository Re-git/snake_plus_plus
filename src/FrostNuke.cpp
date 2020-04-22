#include "FrostNuke.h"

FrostNuke::FrostNuke(Texture2D frostNukesSprite, Area gameArea) {
    sprite = frostNukesSprite;
    frostNukeSize = 45;
    spawnArea = gameArea;
    respawnTimer = new Timer(10000);
    outsideTimer = new Timer(4000);
    outside = false;
    growing = 0.5;
    moveFrostNuke();
}

FrostNuke::~FrostNuke() {
    delete respawnTimer;
}

void FrostNuke::moveFrostNuke() {
    position.x = ((int)std::abs(spawnArea.left + (int)frostNukeSize + rand() % (GetScreenWidth() - spawnArea.right - 2 * (int)frostNukeSize)));
    position.y = ((int)std::abs(spawnArea.top + rand() % (GetScreenHeight() - spawnArea.bottom - 2 * (int)frostNukeSize)));
    collisionMask = { position.x - frostNukeSize / 2,position.y - frostNukeSize / 2,frostNukeSize, frostNukeSize};
}
void FrostNuke::moveFrostNukeOutside() {
    outside = true;
    position.x=-100;
    position.y=-100;
    collisionMask= {position.x-frostNukeSize/2,position.y-frostNukeSize/2,frostNukeSize,frostNukeSize};
    outsideTimer -> reset();
    respawnTimer -> reset();
}

void FrostNuke::draw() {
    if (respawnTimer -> isReady())
    {
        moveFrostNuke();
        respawnTimer -> reset();
    }
    if (outsideTimer -> isReady() && outside)
    {
        moveFrostNuke();
        outside = false;
        respawnTimer -> reset();
    }
    pulse(40.0, 60.0);
    DrawTexturePro(sprite, { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height },
                   { position.x, position.y, frostNukeSize, frostNukeSize },
                   { frostNukeSize / 2, frostNukeSize / 2 }, 0, WHITE);
}

void FrostNuke::pulse(float minSize, float maxSize) {
    frostNukeSize = frostNukeSize + growing;
    if (frostNukeSize < minSize || frostNukeSize == maxSize)
    {
        growing *= -1;
    }
}