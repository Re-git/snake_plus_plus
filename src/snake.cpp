#include "snake.h"

Snake::Snake(int length)
{
    for (int i = 0; i < length; ++i)
    {
        tail.push_back(Vector2{position.x, position.y});
    }
}


void Snake::update()
{
    position = Vector2Add(position, velocity);
    limit(velocity, 4);
    checkCollisionWithEdges(position);
    tail.insert(tail.begin(), Vector2{position.x, position.y});
    tail.erase(tail.end() - 1);
}


void Snake::draw()
{
    // Rysujemy snake'a
    for (size_t i = 0; i < tail.size(); ++i)
    {
        DrawRectangle(tail[i].x, tail[i].y, 4, 4, GREEN);
    }
}


bool Snake::checkCollisionWithEdges(Vector2 &v)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    bool collide = false;
    if (v.x > width)  {v.x = 0;    collide=true;}
    if (v.x < 0)  {v.x = 800; collide=true;}
    if (v.y > height) {v.y = 0;    collide=true;}
    if (v.y < 0) {v.y = 800; collide=true;}
    return collide;
}


void Snake::limit(Vector2 &v, float num)
{
    if (v.x > num)   {v.x = num;}
    if (v.x < -num) {v.x = -num;}
    if (v.y > num)   {v.y = num;}
    if (v.y < -num) {v.y = -num;}
}