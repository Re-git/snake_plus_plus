// Import bibliotek standardowych C/C++
#include "stdlib.h"
#include <ctime>
#include <vector>
#include <iostream>
// Import raylib
#include "libs/raylib.h"
#include "libs/raymath.h"
// Import naszych nagłówków
#include "monkey.h"
#include "snake.h"
#include "timer.h"
#include "Fruits.h"


int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 800;
  SetTargetFPS(60);
  // CREATE WINDOW
  InitWindow(screenWidth, screenHeight, "Snake");
  Vector2 windowPosition = {100, 100};
  SetWindowPosition(windowPosition.x, windowPosition.y);
  // START RANDOM NUMBER GENERATOR
  srand(time(NULL));

  // INITIALIZE VARIABLES
  int numberOfMonkeys = 10;
  std::vector<Malpa> monkeyList;
  Snake snake(10);
  Fruits fruit;
  bool collision = false;

  // wypelniamy liste malp Malpami
  for (int i = 0; i < numberOfMonkeys; i++)
  {
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
    if(snake.collide(fruit.collisionMask))
            fruit.moveFruit();
    // DRAWING
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < numberOfMonkeys; i++)
    {
      monkeyList[i].applyBehaviors(monkeyList, snake.position);
      monkeyList[i].update();
      collision = CheckCollisionRecs(snake.narysowany_snek,monkeyList[i].narysowana_malpa);
      if (collision) 
      {
      ClearBackground(WHITE);
      DrawText("GAME OVER",screenWidth/2-100,screenHeight/2, 30,BLACK);
      // po kolizji moze prowadzic do nieistniejacego jeszcze ekranu smierci/highscrow x)
      }
    }


  static Timer timer(500); // tworzymy timer i ustawiamy go na 0.5 sekundy
  if (timer.isReady())       // sprawdzamy czy już minęły 0.5 sek
    {
      std::cout << timer.isReady() << std::endl;
        monkeyList.push_back(Malpa());
        numberOfMonkeys++;
        timer.reset();        // resetujemy stoper i zaczynamy liczyć 0.5 sek od początku
    }
    
    // std::cout << "Ilosc malpek: " << numberOfMonkeys << std::endl;  // Wypisz w konsoli ilosc malp na ekranie
    snake.update();
    snake.draw();
    fruit.draw();
    EndDrawing();
  }
  // CLEANUP
  CloseWindow();
  return 0;
}

