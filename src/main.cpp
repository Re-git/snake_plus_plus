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

  
  int numberOfMonkeys = 1;
  std::vector<Malpa> monkeyList;
  Snake snake(10);

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

    // DRAWING
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < numberOfMonkeys; i++)
    {
      monkeyList[i].applyBehaviors(monkeyList, snake.position);
      monkeyList[i].update();
    }


  static Timer timer(2000); // tworzymy timer i ustawiamy go na 2 sekundy
  if (timer.isReady())       // sprawdzamy czy już minęły 2 sek
    {
      std::cout << timer.isReady() << std::endl;
        monkeyList.push_back(Malpa());
        numberOfMonkeys++;
        timer.reset();        // resetujemy stoper i zaczynamy liczyć 2 sek od początku
    }
    
    // std::cout << "Ilosc malpek: " << numberOfMonkeys << std::endl;  // Wypisz w konsoli ilosc malp na ekranie
    snake.update();
    snake.draw();
    EndDrawing();
  }
  // CLEANUP
  CloseWindow();
  return 0;
}
