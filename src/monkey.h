#ifndef __MONKEY_H_INCLUDED__
#define __MONKEY_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"
#include <vector>


class Malpa
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float size_width, size_height;
    float r;
    float maxforce;    // Maximum steering force
    float maxspeed;    // Maximum speed
    Rectangle narysowana_malpa;

    Malpa();
    void draw();
    void update();
    void limit(Vector2&, float);
    void applyForce(Vector2);
    void applyBehaviors(std::vector<Malpa>, Vector2);
    Vector2 seek(Vector2);
    Vector2 separate(std::vector<Malpa>);
};

#endif