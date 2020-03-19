#include "monkey.h"


Malpa::Malpa()
{
    position.x = rand() % GetScreenWidth();
    position.y = rand() % GetScreenHeight();
    velocity = Vector2{0,0};
    acceleration = Vector2{0,0};
    size = 20;
    r = 12;
    maxspeed = (rand() % 3) + 1;   // daje wartosci od 3 do 6. Niektóre małpy będą szybsze niż inne.
    maxforce = 0.5;

}


void Malpa::draw()
{
    DrawText("@", position.x, position.y, size, RED);
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
    limit(steer, maxforce);
    
    return steer;
  }

  // Separation
  // Method checks for nearby malpy and steers away
  Vector2 Malpa::separate (std::vector<Malpa> malpy) {
    float desiredseparation = r*2;
    Vector2 sum{0,0};
    int count = 0;
    // For every malpa in the system, check if it's too close
    for (Malpa other : malpy) { 
      float d = Vector2Distance(position, other.position);
      // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
      if ((d > 0) && (d < desiredseparation)) {
        // Calculate vector pointing away from neighbor
        Vector2 diff = Vector2Subtract(position, other.position);
        diff = Vector2Normalize(diff);
        diff = Vector2Divide(diff, d);        // Weight by distance
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
      limit(sum, maxforce);
    }
    return sum;
  }
