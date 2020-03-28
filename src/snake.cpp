#include "snake.h"


Snake::Snake(Texture2D snakeSprite ,int length)
{
    sprite = snakeSprite;  
    headHeight = 30;
    headWidth = 30; 
    bodyHeight = 10;
    bodyWidth = 10; 
    position.x = GetScreenWidth() / static_cast<float>(2.0);
    position.y = GetScreenHeight() / static_cast<float>(2.0);
    velocity = Vector2{4,0};
    maxSpeed = 4;
    turnRate = 0.2;
    speedModifier = 0;
    angle=0;
    for (int i = 0; i < length; ++i)
    {
        tail.push_back(Vector2{position.x, position.y});
    }
}

void Snake::update()
{
    tail.insert(tail.begin(), Vector2{position.x, position.y});
    tail.pop_back();
    move();
    checkCollisionWithEdges(position, collisionSound);
    limitAngle(2*PI);
    limit(velocity, maxSpeed);
}


void Snake::draw()
{
    // Rysujemy snake'a
    for (size_t i = 1; i < tail.size(); ++i)
    {
        DrawLineEx(Vector2{tail[i].x,tail[i].y},Vector2{tail[i-1].x,tail[i-1].y},25,Color{90,180,50,255});
    }
        DrawTexturePro(sprite, {0.0f, 0.0f, (float)sprite.width, (float)sprite.height},
                                     {position.x, position.y, headWidth, headHeight},
                                     {headHeight/2,headHeight/2},0, WHITE);
}

void Snake::move()
{
    velocity.x = cos(angle);      
    velocity.y = sin(angle);
    velocity = Vector2Normalize(velocity);
    velocity = Vector2Scale(velocity, maxSpeed + speedModifier);
    position = Vector2Add(velocity,position);
}

bool Snake::checkCollisionWithEdges(Vector2 &pos,Sound BCS)
{
    collisionSound = BCS;
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    bool collide = false;
    if (pos.x > width-40)  {{pos.x = width-40; PlaySound(BCS);} if(angle>PI) angle=angle-PI-2*angle; else angle=PI-angle;  collide=true;}
    if (pos.x < 41)        {{pos.x = 42; PlaySound(BCS);}        if(angle>PI) angle=2*PI-(angle-PI); else angle=PI-angle;  collide=true; }
    if (pos.y > height-55) {{pos.y = height-55; PlaySound(BCS);} if(angle>PI/2) angle=2*PI-angle; else angle=2*PI-angle;  collide=true; }
    if (pos.y < 116)        {{pos.y = 116; PlaySound(BCS);}       if(angle>1.5*PI) angle=angle-PI-(2*(angle-1.5*PI)); else angle=angle-PI+(2*(1.5*PI-angle));  collide=true;}
    return collide;
}

void Snake::handleInput()
{
    // KEYBOARD INPUT
      if (IsKeyDown(KEY_RIGHT))
      {
        turn(turnRate);
      }
      if (IsKeyDown(KEY_LEFT))
      {
        turn(-turnRate);
      }
      if (IsKeyDown(KEY_UP))
      {
          speedModifier += 0.5;
      }
      if (IsKeyReleased(KEY_UP))
      {
          speedModifier = 0;
      }
      if (IsKeyDown(KEY_DOWN))
      {
        speedModifier = -2;
      }
      if (IsKeyReleased(KEY_DOWN))
      {
        speedModifier = 0;
      }
}

bool Snake::collide(Rectangle rec){
    for (std::size_t i = 0; i < tail.size(); ++i){
        if(CheckCollisionRecs(Rectangle{tail[i].x, tail[i].y, bodyWidth, bodyHeight }, rec) ||
            CheckCollisionRecs(Rectangle{position.x-headWidth/2,position.y-headHeight/2,headWidth,headHeight},rec)) return true;
    }
    return false;
}

void Snake::limit(Vector2 &v, float num)
{
    if (v.x > num)   {v.x = num;}
    if (v.x < -num) {v.x = -num;}
    if (v.y > num)   {v.y = num;}
    if (v.y < -num) {v.y = -num;}
}

void Snake::turn(float r)
{
    angle += r / (0.5 * Vector2Length(velocity));
}

void Snake::limitAngle(float aLimit)
{
    if (angle > 2*PI)
    {
        angle = angle - 2*PI;
    }
    if (angle < -2*PI)
    {
        angle = angle + 2*PI;
    }
}
