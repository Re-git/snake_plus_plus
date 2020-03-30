
#include "Explosion.h"


Explosion::Explosion(Texture2D explosionSprite, Area gameArea) {
    sprite = explosionSprite;
    explosionSize = 150;
    spawnArea = gameArea;
    growing = 0.5;
}

void Explosion::draw(){
    DrawTexturePro(sprite, { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height },
        { position.x, position.y, explosionSize, explosionSize },
        { explosionSize / 2,explosionSize / 2 }, 0, WHITE);
}

void Explosion::moveExplosion(float posX, float posY){

    position.x = posX;
    position.y = posY;
    collisionMask = { position.x - explosionSize / 2,position.y - explosionSize / 2,explosionSize,explosionSize };
}

void Explosion::update(){
    pulse(40.0, 60.0);
}

void Explosion::pulse(float minSize, float maxSize){
    explosionSize = explosionSize + growing;
    if (explosionSize < minSize || explosionSize == maxSize){
        growing *= -1;
    }
}