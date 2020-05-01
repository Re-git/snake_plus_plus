#ifndef __MotoMoto_H_INCLUDED__
#define __MotoMoto_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"
#include "timer.h"
#include <vector>



class MotoMoto{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float width, height;
    float maxspeed;      // Maximum speed
    float maxSeekForce;
    int dead;
    int frozen;
    Rectangle motoMotoRec;
    Texture2D sprite;
    Timer* freeze_timer;

    MotoMoto(Texture2D motoMotoSprite);
    void draw();
    void update();
    void limit(Vector2&, float);
    void applyForce(Vector2);
    void applyBehaviors(std::vector<MotoMoto>&);
    bool collide(Rectangle rec);
    Vector2 createPosition();
    Vector2 seek(Vector2);
};

#endif