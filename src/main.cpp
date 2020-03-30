// Import bibliotek standardowych C/C++
#include "stdlib.h"
#include <ctime>
#include <vector>
#include <iostream>
// Import raylib
#include "libs/raylib.h"
#include "libs/raymath.h"
// Import naszych nagłówków
#include "utility.h"
#include "monkey.h"
#include "snake.h"
#include "timer.h"
#include "Fruits.h"
#include "Nukes.h"
#include "Explosion.h"

enum GameState {mainMenu, inGame, deathScreen, pause} gameState;

int main(void){
  // INITIALIZE VARIABLES
  float screenWidth = 1420;
  float screenHeight = 1000;
  Area gameArea = {5, 65, 5, 5};
  gameState = mainMenu;
  static Timer niezjedzone(10000);
  static Timer nieuzyte(10000);
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
  // LOAD TEXTURES
  Texture2D fruitSprite = LoadTexture("assets/sprites/food/owocek.png");
  Texture2D monkeySprite = LoadTexture("assets/sprites/enemies/monkey.png");
  Texture2D snakeSprite = LoadTexture("assets/sprites/character/snake.png");
  Texture2D groundTile = LoadTexture("assets/sprites/tiles/Ground_Tile_01_C.png");
  Texture2D nukeSprite = LoadTexture("assets/sprites/powerups/3.png");
  Texture2D explosionSprite = LoadTexture("assets/sprites/effects/explosion3.png");
  // CREATE GAME OBJECTS
  Snake snake(snakeSprite, 15);
  std::vector<Malpa> monkeyList;
  Fruits fruit(fruitSprite, gameArea);
  Nukes nuke(nukeSprite, gameArea);
  Explosion explosion(explosionSprite, gameArea);
 

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
      snake = Snake(snakeSprite, 15);
      fruit.moveFruit();
      nuke.moveNuke();
      frameCounter = 0;

      // DRAWING
        BeginDrawing();
        ClearBackground(WHITE);
        text_size = MeasureText("GAME OVER",30);                                                                      
        DrawText("GAME OVER",GetScreenWidth()/2 - text_size/2,GetScreenHeight()/2, 30,BLACK); 
        text_size = MeasureText("YOUR SCORE",30);
        DrawText(TextFormat("YOUR SCORE: %d", points),GetScreenWidth()/2 - text_size/2,GetScreenHeight()/2+ 30, 30,BLACK);
        text_size = MeasureText("PRESS ENTER TO RESTART GAME",20);
        DrawText("PRESS ENTER TO RESTART GAME",GetScreenWidth()/2 - text_size/2,GetScreenHeight()/2+60, 20,BLACK); 
        EndDrawing();
      // KEYBOARD INPUT
        if (IsKeyDown(KEY_ENTER)){
          gameState = inGame;
          niezjedzone.reset();
          czas_punktowy.reset();
          points = 0;
          }

    break;

    case inGame:
      frameCounter++;
      fruit.update();
      nuke.update();
            // niezjedzone jedzenie znika po 10 s
            if(niezjedzone.isReady())
            {
                fruit.moveFruit();
                niezjedzone.reset();
            }
            if (nieuzyte.isReady()){
                nuke.moveNuke();
                nieuzyte.reset();
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
            if (snake.collide(nuke.collisionMask)){
                points = points + monkeyList.size();
                monkeyList.clear();
                nuke.moveNuke();
                nieuzyte.reset();
            }


      // DRAWING
      BeginDrawing();
      ClearBackground(BLACK);
      
      // RAMKA - PRZESTRZEŃ GRY
      // DrawRectangleLines(4,60,screenWidth-8,screenHeight-64,ORANGE);
      for(int x=0;x<(GetScreenWidth()/128)+1;x++)
      {
        for(int y=0;y<(GetScreenHeight()/128)+1;y++)
        {
          DrawTexture(groundTile,x*128,y*128,WHITE);
        }
      }
      // DrawRectangle(6,64,screenWidth-12,screenHeight-69,Color{10,80,40,255});
      // DrawRectangle(0,60,screenWidth,screenHeight,DARKBROWN);
      DrawRectangle(0,0,screenWidth,60, DARKBROWN);
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


    static Timer timer(5000); // tworzymy timer i ustawiamy go na 0.5 sekund
    if (timer.isReady())       // sprawdzamy czy już minęło 0.5 sek
      {
          monkeyList.push_back(Malpa(monkeySprite));
          if (timer.getLimit() > 200)
          {
            timer.setLimit(timer.getLimit() - 1);
          }
          
          timer.reset();        // resetujemy stoper i zaczynamy liczyć 5 sek od początku
      }
      


      snake.handleInput();
      snake.update();
      snake.draw();
      fruit.draw();
      nuke.draw();
      EndDrawing();
    break;
    
    default:
      std::cout << "INVALID GAME STATE" << std::endl;
    break;
    }

  }
  // CLEANUP
  CloseWindow();
  UnloadTexture(snakeSprite);
  UnloadTexture(monkeySprite);
  UnloadTexture(fruitSprite);
  UnloadTexture(nukeSprite);
  UnloadTexture(explosionSprite);
  return 0;
}

