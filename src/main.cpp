// Import bibliotek standardowych C/C++
#include "stdlib.h"
#include <ctime>
#include <vector>
// Import raylib
#include "libs/raylib.h"
#include "libs/raymath.h"
// Import naszych nagłówków
#include "monkey.h"
#include "snake.h"


int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 800;
  SetTargetFPS(60);
  // CREATE WINDOW
  InitWindow(screenWidth, screenHeight, "Snake");
  Vector2 windowPosition = {100, 100};
  SetWindowPosition(windowPosition.x, windowPosition.y);
  srand(time(NULL));
  
  const int numberOfMonkeys = 100;
  std::vector<Malpa> monkeyList;
  Snake snake(10);
  // Malpa pojedyncza_malpa;
  // Rectangle boxCollision = { 0 };
  bool collision = false;

  // wypelniamy liste malp Malpami
  for (int i = 0; i < numberOfMonkeys; i++)
  {
    //pojedyncza_malpa.draw();
    monkeyList.push_back(Malpa());
  }

  // To jest główna pętla, wykonywana dopóki okno nie zostanie zamknięte
  while (!WindowShouldClose())
  {
    // KEYBOARD INPUT
    if (IsKeyDown(KEY_RIGHT))
      snake.acceleration.x += .2;
    if (IsKeyDown(KEY_LEFT))
      snake.acceleration.x += -.2;
    if (IsKeyDown(KEY_UP))
      snake.acceleration.y += -.2;
    if (IsKeyDown(KEY_DOWN))
      snake.acceleration.y += .2;
    
    // kolizja 
    // collision = CheckCollisionRecs(snake.narysowany_snek,pojedyncza_malpa.narysowana_malpa);  
    // if (collision) boxCollision = GetCollisionRec(snake.narysowany_snek, pojedyncza_malpa.narysowana_malpa);

    // DRAWING
    BeginDrawing();
    ClearBackground(BLACK);
    // pojedyncza_malpa.draw();

    for (int i = 0; i < numberOfMonkeys; i++)
    {
      monkeyList[i].applyBehaviors(monkeyList, snake.position);
     // monkeyList[i].moveTo(snake.position, 0.2);
      monkeyList[i].update();
      collision = CheckCollisionRecs(snake.narysowany_snek,monkeyList[i].narysowana_malpa);
      
      // pojedyncza_malpa.applyBehaviors(monkeyList,snake.position);
      // pojedyncza_malpa.update();

      if (collision) 
      {
      ClearBackground(WHITE);
      DrawText("GAME OVER",screenWidth/2-100,screenHeight/2, 30,BLACK);
      // po kolizji moze prowadzic do nieistniejacego jeszcze ekranu smierci/highscrow x)
      // DrawRectangleRec(boxCollision, LIME);
      }
    }

    snake.update();
    snake.draw();

    //warunek kolizyjny zewnetrzna opcja
    // if (collision) 
    // {
      // ClearBackground(WHITE);
      // DrawText("GAME OVER",screenWidth/2,screenHeight/2, 30,BLACK);
      // DrawRectangleRec(boxCollision, LIME);
    // }

    EndDrawing();
  }
  // CLEANUP
  CloseWindow();
  return 0;
}
