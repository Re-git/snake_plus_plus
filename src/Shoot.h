#ifndef __SHOOT_H_INCLUDED__
#define __SHOOT_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"
#include "timer.h"
#include <vector>


class Shoot {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float width, height;
    float maxspeed;      // Maximum speed
    float maxSeekForce;
    Rectangle kissRec;
    Texture2D sprite;
    int frozen;
    int dead;
    Vector2 direction;
    Timer* freeze_timer;
    Shoot(Texture2D kissSprite, Vector2 hippoPosition);
    void draw();
    void update();
    void limit(Vector2&, float);
    void applyForce(Vector2);
    void applyBehaviors(std::vector<Shoot>&);
    bool collide(Rectangle rec);
    Vector2 createPosition();
    Vector2 seek(Vector2);
};

#endif