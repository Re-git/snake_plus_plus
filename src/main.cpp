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

enum GameState {mainMenu, inGame, deathScreen} gameState;

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 800;
  gameState = mainMenu;
  SetTargetFPS(60);
  // CREATE WINDOW
  InitWindow(screenWidth, screenHeight, "Snake");
  Vector2 windowPosition = {100, 100};
  SetWindowPosition(windowPosition.x, windowPosition.y);
  // START RANDOM NUMBER GENERATOR
  srand(time(NULL));

  // INITIALIZE VARIABLES
  std::vector<Malpa> monkeyList;
  Snake snake(15);
  Fruits fruit;
  bool collision = false;


  // To jest główna pętla, wykonywana dopóki okno nie zostanie zamknięte
  while (!WindowShouldClose())
  {
    switch (gameState)
    {
    case mainMenu:
      // KEYBOARD INPUT
      if (IsKeyDown(KEY_ENTER))
        gameState = inGame;
      // DRAWING
      BeginDrawing();
      ClearBackground(BROWN);
      DrawText("PRESS ENTER",screenWidth/2-100,screenHeight/2, 30,BLACK);
      EndDrawing();
    break;

    case deathScreen:
      // CLEANUP
      monkeyList.clear();
      snake = Snake(15);
      // KEYBOARD INPUT
      if (IsKeyDown(KEY_ENTER))
        gameState = inGame;
      // DRAWING
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("GAME OVER",screenWidth/2-100,screenHeight/2, 30,BLACK);
        DrawText("PRESS ENTER TO RESTART GAME",screenWidth/2-100,screenHeight/2+30, 20,BLACK);
        EndDrawing();
    break;

    case inGame:
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
      for (Malpa &m : monkeyList)  // for every monkey in monkey list
      {
        m.applyBehaviors(monkeyList, snake.position);
        m.update();
        collision = CheckCollisionRecs(snake.narysowany_snek, m.narysowana_malpa);
        if (collision) 
        {
          gameState = deathScreen;
        }
      }


    static Timer timer(500); // tworzymy timer i ustawiamy go na 0.5 sekundy
    if (timer.isReady())       // sprawdzamy czy już minęły 0.5 sek
      {
        std::cout << timer.isReady() << std::endl;
          monkeyList.push_back(Malpa());
          timer.reset();        // resetujemy stoper i zaczynamy liczyć 0.5 sek od początku
      }
      
      // std::cout << "Ilosc malpek: " << numberOfMonkeys << std::endl;  // Wypisz w konsoli ilosc malp na ekranie
      snake.update();
      snake.draw();
      fruit.draw();
      EndDrawing();
    break;
    
    default:
      std::cout << "INVALID GAME STATE" << std::endl;
    break;
    }

  }
  // CLEANUP
  CloseWindow();
  return 0;
}

