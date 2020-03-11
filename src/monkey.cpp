#include "monkey.h"


Malpa::Malpa()
{
    position.x = rand() % GetScreenWidth();
    position.y = rand() % GetScreenHeight();
    velocity = Vector2{0,0};
    acceleration = Vector2{0,0};
    size = rand() % 100;
}


void Malpa::draw()
{
    DrawText("@", position.x, position.y, size, BROWN);
}

void Malpa::update()
{
    move();
    draw();
}

void Malpa::move()
{
    velocity = Vector2Add(acceleration,velocity);
    position = Vector2Add(velocity,position);
    acceleration = Vector2Zero();
    limit(velocity,2);
}

void Malpa::moveTo(Vector2 vec, float speed)
{
    Vector2 force = Vector2Subtract(vec, position); 
    force = Vector2Normalize(force);
    force = Vector2MultiplyV(force, Vector2{speed,speed});
    acceleration = Vector2Add(force, acceleration);
}

void Malpa::limit(Vector2 &v, float num)
{
    if (v.x > num)   {v.x = num;}
    if (v.x < -num) {v.x = -num;}
    if (v.y > num)   {v.y = num;}
    if (v.y < -num) {v.y = -num;}
}