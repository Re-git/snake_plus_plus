#ifndef __MONKEY_H_INCLUDED__
#define __MONKEY_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"
#include "timer.h"
#include <vector>


class Malpa
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float width, height;
    float separationRange;
    float maxspeed;      // Maximum speed
    float maxSeparationForce; // siła odpychania się między małpkami
    float maxSeekForce;
    int dead;
    int frozen;
    int buffed;
    Color color;
    Timer* freeze_timer;
    Rectangle monkeyRec;
    Texture2D sprite;

    Malpa(Texture2D monkeySprite);
    void draw();
    void update();
    void limit(Vector2&, float);
    void applyForce(Vector2);
    void applyBehaviors(std::vector<Malpa>&, Vector2);
    Vector2 createPosition();
    Vector2 seek(Vector2);
    Vector2 separate(std::vector<Malpa>&);
};

#endif