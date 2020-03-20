#include "snake.h"

Snake::Snake(int length)
{
    position.x = GetScreenWidth() / static_cast<float>(2.0);
    position.y = GetScreenHeight() / static_cast<float>(2.0);
    velocity = Vector2{0,0};
    acceleration = Vector2{0,0};
    for (int i = 0; i < length; ++i)
    {
        tail.push_back(Vector2{position.x, position.y});
    }
}


void Snake::update()
{
    checkCollisionWithEdges(position);
    tail.insert(tail.begin(), Vector2{position.x, position.y});
    tail.erase(tail.end() - 1);
    move();
    limit(velocity, 4);
}


void Snake::draw()
{
    // Rysujemy snake'a
    for (std::size_t i = 0; i < tail.size(); ++i)
    {
         narysowany_snek = {tail[i].x, tail[i].y, 4, 4};	
        DrawRectangleRec(narysowany_snek,GREEN);
    }
}

void Snake::move()
{
    velocity = Vector2Add(acceleration,velocity);
    position = Vector2Add(velocity,position);
    acceleration = Vector2Zero();
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
bool Snake::collide(Rectangle rec){
    for (std::size_t i = 0; i < tail.size(); ++i){
        if(CheckCollisionRecs(Rectangle{tail[i].x, tail[i].y, 4, 4}, rec)) return true;
    }
    return false;
}