
#include "Explosion.h"


Explosion::Explosion(Texture2D sprite[5],float x, float y, size_t tailSize) {
    sprites[0] = sprite[0];
    sprites[1] = sprite[1];
    sprites[2] = sprite[2];
    sprites[3] = sprite[3];
    sprites[4] = sprite[4];
    position.x = x;
    position.y = y;
    explosionSize = tailSize + 150;
    frame = 0;
    finished = 0;
}

void Explosion::draw(){
    DrawTexturePro(sprites[frame/2], { 0.0f, 0.0f, (float)sprites[frame/2].width, (float)sprites[frame/2].height },
        { position.x, position.y, explosionSize, explosionSize },
        { explosionSize / 2,explosionSize / 2 }, 0, WHITE);      
}

void Explosion::update(){
        if (frame<8)
        {
           frame++;
        }
        else
        {
            finished = 1;
        }
}
