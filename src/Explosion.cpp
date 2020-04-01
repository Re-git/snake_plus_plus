
#include "Explosion.h"


Explosion::Explosion(Texture2D sprite[4],float x, float y) {
    sprites[0] = sprite[0];
    sprites[1] = sprite[1];
    sprites[2] = sprite[2];
    sprites[3] = sprite[3];
    position.x = x;
    position.y = y;
    explosionSize = 150;
    frame = 0;
}

void Explosion::draw(){
    DrawTexturePro(sprites[frame], { 0.0f, 0.0f, (float)sprites[frame].width, (float)sprites[frame].height },
        { position.x, position.y, explosionSize, explosionSize },
        { explosionSize / 2,explosionSize / 2 }, 0, WHITE);      
}

void Explosion::update(){
        if (frame<4)
        {
           frame++;
        }
        else
        {
            frame = 0;
        }
}
