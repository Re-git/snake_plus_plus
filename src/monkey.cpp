#include "monkey.h"
#include <iostream>

Malpa::Malpa(Texture2D monkeySprite)
{
    sprite = monkeySprite;
    position = createPosition();
    velocity = Vector2{0,0};
    acceleration = Vector2{0,0};
    width = 50;
    height = 50;
    separationRange = 900;              // odległość jaką małpki starają się utrzymać pomiędzy sobą
    maxspeed = 1.5;                       // max prędkość danej małpki
    maxSeparationForce = 0.015;       // siła odpychania się między małpkami
    maxSeekForce = 0.055;               // siła z jaką małpki zmieniają swoją trajektorie żeby podążać za graczem

}

void Malpa::draw()
{
    monkeyRec = {position.x,position.y,width, height};
    DrawTexturePro(sprite, {0.0f, 0.0f, (float)sprite.width, (float)sprite.height},
                        monkeyRec, {0.0f, 0.0f},0.0f, WHITE);
}

void Malpa::update()
{
    // Update velocity
    velocity = Vector2Add(velocity, acceleration);
    // Limit speed
    limit(velocity, maxspeed);
    position = Vector2Add(position, velocity);
    // Reset accelertion to 0 each cycle
    acceleration = Vector2Scale(acceleration,0);
    draw();
    maxspeed += 0.001;
    if (separationRange > 60)
    {
      separationRange -= 0.1;
    }    
}


void Malpa::applyForce(Vector2 force) {
    // We could add mass here if we want A = F / M
    acceleration = Vector2Add(acceleration, force);
  }

void Malpa::limit(Vector2 &v, float num)
{
    if (v.x > num)   {v.x = num;}
    if (v.x < -num) {v.x = -num;}
    if (v.y > num)   {v.y = num;}
    if (v.y < -num) {v.y = -num;}
}

void Malpa::applyBehaviors(std::vector<Malpa> malpy, Vector2 snakePosition) {
     Vector2 separateForce = separate(malpy);
     Vector2 seekForce = seek(snakePosition);
     separateForce = Vector2Scale(separateForce, 2);
     seekForce = Vector2Scale(seekForce,1);
     applyForce(separateForce);
     applyForce(seekForce); 
  }
  
// A method that calculates a steering force towards a target
// STEER = DESIRED MINUS VELOCITY
Vector2 Malpa::seek(Vector2 target) {
    Vector2 desired = Vector2Subtract(target,position);  // A vector pointing from the position to the target
    
    // Normalize desired and scale to maximum speed
    desired = Vector2Normalize(desired);
    desired = Vector2Scale(desired,maxspeed);
    // Steering = Desired minus velocity
    Vector2 steer = Vector2Subtract(desired,velocity);
    limit(steer, maxSeekForce);
    
    return steer;
  }

// Separation
// Method checks for nearby malpy and steers away
Vector2 Malpa::separate (std::vector<Malpa> malpy) {
  Vector2 sum{0,0};
  int count = 0;
  // For every malpa in the system, check if it's too close
  for (Malpa other : malpy) { 
    float d = Vector2Distance(position, other.position);
    // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
    if ((d > 0) && (d < separationRange)) {
      // Calculate vector pointing away from neighbor
      Vector2 diff = Vector2Subtract(position, other.position);
      diff = Vector2Normalize(diff);
      diff = Vector2Divide(diff, d*d);        // Weight by distance
      sum = Vector2Add(sum, diff);
      count++;            // Keep track of how many
    }
  }
  // Average -- divide by how many
  if (count > 0) {
    sum = Vector2Divide(sum,count);
    // Our desired vector is the average scaled to maximum speed
    sum = Vector2Normalize(sum);
    sum = Vector2Scale(sum, maxspeed);
    // Implement Reynolds: Steering = Desired - Velocity
    sum = Vector2Subtract(sum, velocity);
    limit(sum, maxSeparationForce);
  }
  return sum;
}

Vector2 Malpa::createPosition()
{
  Vector2 vec;
  int roll = GetRandomValue(1,4);
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
    vec.y = GetScreenHeight()+height;
    break;
  
  default:
    break;
  }
  return vec;
}
