#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"
#include <vector>
// g++ main.cpp -std=c++17 `pkg-config --libs --cflags raylib` && ./a.out



class Snake
{
public:
  std::vector<Vector2> tail;
  Vector2 position = {100, 100};
  Vector2 velocity = {0, 0};
//   bool alive = true;
  Snake(int length)
  {
    for (int i = 0; i < length; ++i) {
      tail.push_back(Vector2{position.x, position.y});
    }
  }

  void update() {
    position = Vector2Add(position,velocity);
    if(velocity.x > 4){velocity.x = 4;}
    if(velocity.x < -4){velocity.x = -4;}
    if(velocity.y > 4){velocity.y = 4;}
    if(velocity.y < -4){velocity.y = -4;}
    tail.insert(tail.begin(), Vector2{position.x, position.y});
    tail.erase(tail.end()-1);

    if(position.x > 800) {position.x = 0;}
    if(position.x < 0) {position.x = 800;}
    if(position.y > 800) {position.y = 0;}
    if(position.y < 0) {position.y = 800;}
  }

  void draw() {
    // Rysujemy snake'a
    for (size_t i = 0; i < tail.size(); ++i) {
      DrawRectangle(tail[i].x, tail[i].y, 4, 4, GREEN);
    }
  }

//   boolean collide_with_red()
//   {
//     color_under_snake = get((int)snake.position.x, (int)snake.position.y);
//     if (red(color_under_snake) > 170) 
//     {
//       return true;
//     } else {
//       return false;
//     }
//   }

//   bool collide_with_border()
//   {
//     if (snake.position.x < 0 | snake.position.x > width | snake.position.y < 0 | snake.position.y > height)
//     {
//       return true;
//     } else {
//       return false;
//     }
//   }
};

class Malpa
{
public:
  float x;
  float y;
  float size;
  int fade = 0;
  int fade_speed = 1;

  Malpa(float s)
  {
    x = rand()*800;
    y = rand()*800;
    size = rand()*100;
    fade = int(s);
  }

  void rysuj_malpe()
  {
    if (fade>255)
    {
      fade=0;
      fade_speed = int(rand()*5);
      x = rand()*800;
      y = rand()*800;
    }
    DrawText("@", rand()*800,rand()*800,40,RED);    
    fade = fade+fade_speed;
  }
};


Snake snake(100);
int ilosc_malp = 20;
std::vector<Malpa> malpy;

int main(void)
{
    srand(time(NULL));
    const int screenWidth = 800;
    const int screenHeight = 800;
    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Snake");
    Vector2 windowPosition = { 500, 200 };
    SetWindowPosition(windowPosition.x, windowPosition.y);

    for (int i=0; i<ilosc_malp; i++) {
    malpy.push_back(Malpa(rand()*155));
  }

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) snake.velocity.x += .2;
        if (IsKeyDown(KEY_LEFT)) snake.velocity.x += -.2;
        if (IsKeyDown(KEY_UP)) snake.velocity.y += -.2;
        if (IsKeyDown(KEY_DOWN)) snake.velocity.y += .2;

        for (int i=0; i<ilosc_malp; i++) {
            malpy[i].rysuj_malpe();
        }

        ClearBackground(BLACK);
        BeginDrawing();
        snake.update();
        snake.draw();
        EndDrawing();
    }
    
    CloseWindow();  
    return 0;
}
