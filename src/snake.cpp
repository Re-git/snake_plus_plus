#include "snake.h"


Snake::Snake(int length)
{
    sprite = LoadTexture("assets/sprites/snake.png");  
    headHeight = 30;
    headWidth = 30; 
    bodyHeight = 10;
    bodyWidth = 10; 
    position.x = GetScreenWidth() / static_cast<float>(2.0);
    position.y = GetScreenHeight() / static_cast<float>(2.0);
    velocity = Vector2{3,0};
    maxSpeed = 5;
    turnRate = 0.2;
    for (int i = 0; i < length; ++i)
    {
        tail.push_back(Vector2{position.x, position.y});
    }
}


void Snake::update()
{
    tail.insert(tail.begin(), Vector2{position.x, position.y});
    tail.erase(tail.end() - 1);
    move();
    checkCollisionWithEdges(position);
    limit(velocity, maxSpeed);
}


void Snake::draw()
{
    // Rysujemy snake'a
    for (std::size_t i = 1; i < tail.size(); ++i)
    {
        DrawRectangleRec({tail[i].x, tail[i].y, bodyWidth, bodyHeight},GREEN);
    }
        DrawTexturePro(sprite, {0.0f, 0.0f, (float)sprite.width, (float)sprite.height},
                                     {position.x, position.y, headWidth, headHeight},
                                     {(float)(10+(headWidth)/2), (float)((headHeight)/2)},
                                     angle*RAD2DEG, WHITE);
}

void Snake::move()
{
    float  vectorLength = Vector2Length(velocity);
    velocity.x = cos(angle);      
    velocity.y = sin(angle);
    velocity = Vector2Normalize(velocity);
    velocity = Vector2Scale(velocity, vectorLength);
    position = Vector2Add(velocity,position);
}

bool Snake::checkCollisionWithEdges(Vector2 &pos)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    bool collide = false;
    std::cout << "SNAKE ANGLE:" << angle << std::endl;
    if (pos.x > width-8)  {pos.x = width-8;  if(angle>PI) angle=angle-PI+2*angle; else angle=PI-angle;  collide=true;}
    if (pos.x < 4)        {pos.x = 4;        if(angle>PI) angle=2*PI-(angle-PI); else angle=PI-angle;  collide=true;}
    if (pos.y > height-7) {pos.y = height-7;  if(angle>PI/2) angle=2*PI-angle; else angle=2*PI-angle;  collide=true;}
    if (pos.y < 60)        {pos.y = 60;        if(angle>1.5*PI) angle=angle-PI-(2*(angle-1.5*PI)); else angle=angle-PI+(2*(1.5*PI-angle));  collide=true;}
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
        if(CheckCollisionRecs(Rectangle{tail[i].x, tail[i].y, bodyWidth, bodyHeight}, rec)) return true;
    }
    return false;
}
void Snake::turn(float r)
{
    angle += r / (0.5 * Vector2Length(velocity));
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
          velocity = Vector2Scale(velocity, 1.3);
      }
      if (IsKeyDown(KEY_DOWN))
      {
        if (Vector2Length(velocity) > 2)
        {
            velocity = Vector2Scale(velocity, 0.95);
        }
      }
}


