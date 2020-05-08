#include "MotoMoto.h"
#include <iostream>

MotoMoto::MotoMoto(Texture2D motoMotoSprite) {
    sprite = motoMotoSprite;
    position = createPosition();
    velocity = Vector2{ 0,0 };
    acceleration = Vector2{ 0,0 };
    width = 100;
    height = 100;
    maxspeed = 3;
    maxSeekForce = 0.055;
    dead = 0;
    frozen = 0;
    freeze_timer = nullptr;

}

void MotoMoto::draw()
{
    motoMotoRec = { position.x,position.y,width, height };
    DrawTexturePro(sprite, { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height },
        motoMotoRec, { 0.0f, 0.0f }, 0.0f, (frozen == 0) ? WHITE : SKYBLUE);
}

void MotoMoto::update() {
    // Update velocity
    velocity = Vector2Add(velocity, acceleration);
    // Limit speed
    limit(velocity, maxspeed);
    position = Vector2Add(position, velocity);
    // Reset accelertion to 0 each cycle
    acceleration = Vector2Scale(acceleration, 0);
    draw();
    // maxspeed += 0.001;
    if (frozen == 1 && freeze_timer->isReady())
    {
        frozen = 0;
        maxspeed = 1.5;
        delete freeze_timer;
    }
}
bool MotoMoto::collide(Rectangle rec) {
    if (CheckCollisionRecs(motoMotoRec, rec)) {
        return true;
    }
    else {
        return false;
    }
}

void MotoMoto::applyForce(Vector2 force) {
    // We could add mass here if we want A = F / M
    acceleration = Vector2Add(acceleration, force);
}

void MotoMoto::limit(Vector2& v, float num)
{
    if (v.x > num) { v.x = num; }
    if (v.x < -num) { v.x = -num; }
    if (v.y > num) { v.y = num; }
    if (v.y < -num) { v.y = -num; }
}

void MotoMoto::applyBehaviors(std::vector<MotoMoto>& hippo) { 
    Vector2 destination = createPosition();
    Vector2 seekForce = seek(destination);
    seekForce = Vector2Scale(seekForce, 1);
    applyForce(seekForce);
}
// A method that calculates a steering force towards a target
// STEER = DESIRED MINUS VELOCITY
Vector2 MotoMoto::seek(Vector2 target) {
    Vector2 desired = Vector2Subtract(target, position);  // A vector pointing from the position to the target

    // Normalize desired and scale to maximum speed
    desired = Vector2Normalize(desired);
    desired = Vector2Scale(desired, maxspeed);
    // Steering = Desired minus velocity
    Vector2 steer = Vector2Subtract(desired, velocity);
    limit(steer, maxSeekForce);

    return steer;
}
Vector2 MotoMoto::createPosition() {
    Vector2 vec;
   
    int roll = GetRandomValue(1, 4);
    switch (roll)
    {
    case 1:
        vec.x = -width;
        vec.y = rand() % GetScreenHeight();
        break;
    case 2:
        vec.x = rand() % GetScreenWidth();
        vec.y = -height;
        break;
    case 3:
        vec.x = GetScreenWidth() + width;
        vec.y = rand() % GetScreenHeight();
        break;
    case 4:
        vec.x = rand() % GetScreenWidth();
        vec.y = GetScreenHeight() + height;
        break;

    default:
        break;
    }
    return vec;
}
