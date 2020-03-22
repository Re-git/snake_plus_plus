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

int main(void){
  // INITIALIZE VARIABLES
  float screenWidth = 1420;
  float screenHeight = 1000;
  Rectangle gameArea = {screenWidth/2, screenHeight/2+65, screenWidth-10, screenHeight-75};
  gameState = mainMenu;
  static Timer niezjedzone(10000);
  static Timer czas_punktowy(5000);      //5 sekund czasu gry
  static int frameCounter, points;
  int text_size;
  // CREATE WINDOW
  SetTargetFPS(60);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow((int)screenWidth, (int)screenHeight, "Snake");
  Vector2 windowPosition = {100, 100};
  SetWindowPosition(windowPosition.x, windowPosition.y);
  // START RANDOM NUMBER GENERATOR
  srand(time(NULL));

  Snake snake(15);
  std::vector<Malpa> monkeyList;
  Fruits fruit(gameArea);


  // To jest główna pętla, wykonywana dopóki okno nie zostanie zamknięte
  while (!WindowShouldClose())
  {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    switch (gameState)
    {
    case mainMenu:
      // KEYBOARD INPUT
      if (IsKeyDown(KEY_ENTER)){
        gameState = inGame;
        niezjedzone.reset();
        czas_punktowy.reset();}
      // DRAWING
      ClearBackground(BROWN);
      BeginDrawing();
      text_size = MeasureText("PRESS ENTER",30);
      DrawText("PRESS ENTER",screenWidth/2 - text_size/2,screenHeight/2, 30,BLACK);
      EndDrawing();
    break;

    case deathScreen:
      // CLEANUP
      monkeyList.clear();
      snake = Snake(15);
      fruit.moveFruit();
      frameCounter = 0;

      // DRAWING
      while (gameState == deathScreen)
      {
        BeginDrawing();
        ClearBackground(WHITE);
        text_size = MeasureText("GAME OVER",30);                                                                      
        DrawText("GAME OVER",screenWidth/2 - text_size/2,screenHeight/2, 30,BLACK);                                 //krzywe po resize
        text_size = MeasureText("YOUR SCORE",30);
        DrawText(TextFormat("YOUR SCORE: %d", points),screenWidth/2 - text_size/2,screenHeight/2+ 30, 30,BLACK);    //krzywe po resize
        text_size = MeasureText("PRESS ENTER TO RESTART GAME",20);                                                  //krzywe po resize
        DrawText("PRESS ENTER TO RESTART GAME",screenWidth/2 - text_size/2,screenHeight/2+60, 20,BLACK);            //krzywe po resize
        EndDrawing();
      // KEYBOARD INPUT
        if (IsKeyDown(KEY_ENTER)){
          gameState = inGame;
          niezjedzone.reset();
          czas_punktowy.reset();
          points = 0;
          }
      }
    break;

    case inGame:
      frameCounter++;
            // niezjedzone jedzenie znika po 10 s
            if(niezjedzone.isReady())
            {
                fruit.moveFruit();
                niezjedzone.reset();
            }

            if(snake.collide(fruit.collisionMask))
      {
          points+=10;
          fruit.moveFruit();
          niezjedzone.reset();
          for (size_t i = 0; i < 2; i++)
          {
            snake.tail.push_back(Vector2{snake.position.x, snake.position.y});
          }                
      }


      // DRAWING
      BeginDrawing();
      ClearBackground(BLACK);
      
      // RAMKA - PRZESTRZEŃ GRY
      // DrawRectangleLines(4,60,screenWidth-8,screenHeight-64,ORANGE);
      DrawRectangle(0,60,screenWidth,screenHeight,PURPLE);
      DrawRectangle(6,64,screenWidth-12,screenHeight-69,BLACK);
      DrawRectangle(0,0,screenWidth,60, PURPLE);
      DrawText(TextFormat("PUNKTY: %d",points),30,15,35,RAYWHITE);
      DrawText(TextFormat("CZAS: %d",frameCounter/60),screenWidth-200,15,35,RAYWHITE);

      // 1 punkt za 5 sekund przezycia

      if(czas_punktowy.isReady())
      {
      points++;
      czas_punktowy.reset(); 
      }
      
      for (Malpa &m : monkeyList)  // for every monkey in monkey list
      {
        m.applyBehaviors(monkeyList, snake.position);
        m.update();
        if (snake.collide(m.monkeyRec)) 
        {
          gameState = deathScreen;
          frameCounter = 0;
        }
      }


    static Timer timer(2000); // tworzymy timer i ustawiamy go na 0.5 sekund
    if (timer.isReady())       // sprawdzamy czy już minęło 0.5 sek
      {
          monkeyList.push_back(Malpa());
          timer.reset();        // resetujemy stoper i zaczynamy liczyć 5 sek od początku
      }
      


      snake.handleInput();
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

