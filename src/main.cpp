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

enum GameState {mainMenu, inGame, deathScreen, pause} gameState;

int main(void)
{
  int screenWidth = 1200;
  int screenHeight = 800;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  gameState = mainMenu;
  int text_size;
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


  // To jest główna pętla, wykonywana dopóki okno nie zostanie zamknięte
  while (!WindowShouldClose())
  {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    switch (gameState)
    {
    case mainMenu:
      // KEYBOARD INPUT
      if (IsKeyDown(KEY_ENTER))
        gameState = inGame;
      // DRAWING
      BeginDrawing();
      ClearBackground(BROWN);
      text_size = MeasureText("PRESS ENTER",30);
      DrawText("PRESS ENTER",screenWidth/2 - text_size/2,screenHeight/2, 30,BLACK);
      EndDrawing();
    break;

    case deathScreen:
      // CLEANUP
      monkeyList.clear();
      snake = Snake(15);
      fruit.moveFruit();
      // KEYBOARD INPUT
      if (IsKeyDown(KEY_ENTER))
        gameState = inGame;
      // DRAWING
        BeginDrawing();
        ClearBackground(WHITE);
        text_size = MeasureText("GAME OVER",30);
        DrawText("GAME OVER",screenWidth/2 - text_size/2,screenHeight/2, 30,BLACK);
        text_size = MeasureText("PRESS ENTER TO RESTART GAME",20);
        DrawText("PRESS ENTER TO RESTART GAME",screenWidth/2 - text_size/2,screenHeight/2+30, 20,BLACK);
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
        if (snake.collide(m.narysowana_malpa)) 
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

