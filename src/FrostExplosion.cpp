#include "FrostExplosion.h"

FrostExplosion::FrostExplosion(Texture2D sprite[5],float x, float y, size_t tailSize) {
    sprites[0] = sprite[0];
    sprites[1] = sprite[1];
    sprites[2] = sprite[2];
    sprites[3] = sprite[3];
    sprites[4] = sprite[4];
    position.x = x;
    position.y = y;
    frostExplosionSize = tailSize * 8;
    frame = 0;
    finished = 0;
}

void FrostExplosion::draw(){
    DrawTexturePro(sprites[frame/2], { 0.0f, 0.0f, (float)sprites[frame/2].width, (float)sprites[frame/2].height },
                   { position.x, position.y, frostExplosionSize, frostExplosionSize },
                   { frostExplosionSize / 2, frostExplosionSize / 2 }, 0, WHITE);
}

void FrostExplosion::update(){
    if (frame<8)
    {
        frame++;
    }
    else
    {
        finished = 1;
    }
}
