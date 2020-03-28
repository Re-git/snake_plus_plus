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


enum GameState {mainMenu, inGame, deathScreen, pause} gameState;

int main(void){
  // INITIALIZE VARIABLES
  float screenWidth = 1420;
  float screenHeight = 1000;
  Area gameArea = {40, 80, 40, 80};
  gameState = mainMenu;
  static Timer niezjedzone(10000);
  static Timer czas_punktowy(5000);      //5 sekund czasu gry
  static int frameCounter, points;
  int text_size;
  InitAudioDevice();
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
  Texture2D groundTile = LoadTexture("assets/sprites/tiles/Ground_Tile_01_B.png");
  Texture2D fenceSprite = LoadTexture("assets/sprites/tiles/bush_pionowy.png");
  Texture2D fenceSprite_side = LoadTexture("assets/sprites/tiles/bush_poziomy.png");
  Texture2D fenceSprite_side_rotated = LoadTexture("assets//sprites/tiles/bush_poziomy_odbity.png");
  Sound BCS = LoadSound("assets/sounds/phaseJump1.ogg");  //BCS-BorderCollisionSound
  Music IGS = LoadMusicStream("assets/soundtrack/neogauge.mp3"); //IGS-InGameSoundtrack
  Sound GameOver= LoadSound("assets/voiceOver/game_over.ogg");
  SetMusicVolume(IGS, 0.2);
  // CREATE GAME OBJECTS
  Snake snake(snakeSprite, 15);
  std::vector<Malpa> monkeyList;
  Fruits fruit(fruitSprite, gameArea);

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
      StopMusicStream(IGS);
      monkeyList.clear();
      snake = Snake(snakeSprite, 15);
      fruit.moveFruit();
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

      UpdateMusicStream(IGS);
      if(IsMusicPlaying(IGS)== false)
      {
          UpdateMusicStream(IGS);
          PlayMusicStream(IGS);
      }
      frameCounter++;
      fruit.update();
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
      //RYSOWANIE PODŁOGI
      for(int x=0;x<(GetScreenWidth()/128)+1;x++)
      {
        for(int y=0;y<(GetScreenHeight()/128)+1;y++)
        {
          DrawTexture(groundTile,x*128,y*128,WHITE);  
                  
        }
      }

      //GÓRNA CZĘŚĆ GUI
      DrawRectangle(0,0,screenWidth,60, Color{8,8,8,133});
      DrawText(TextFormat("PUNKTY: %d",points),30,15,35,RAYWHITE);
      DrawText(TextFormat("CZAS: %d",frameCounter/60),screenWidth-200,15,35,RAYWHITE);

      //RYSOWANIE RAMECZKI - BUSH
      for(int x = 0; x<(GetScreenWidth()+1); x=x+127)
      {
        DrawTexture(fenceSprite_side,x,58,WHITE);
        DrawTexture(fenceSprite_side_rotated,x,GetScreenHeight()-50,WHITE);
        
      }

      for(int y = 60; y<(GetScreenHeight()-44); y=y+70)
      {
        DrawTexture(fenceSprite,0,y,WHITE);
        DrawTexture(fenceSprite,GetScreenWidth()-40,y,WHITE);
      }





      if(czas_punktowy.isReady())   // 1 punkt za 5 sekund przezycia
      {
      points++;
      czas_punktowy.reset(); 
      }
      if(snake.checkCollisionWithEdges(snake.position,BCS)==true) PlaySound(BCS);

      for (Malpa &m : monkeyList)  // for every monkey in monkey list
      {
        m.applyBehaviors(monkeyList, snake.position);
        m.update();
        if (snake.collide(m.monkeyRec)) 
        {
          gameState = deathScreen;
          PlaySound(GameOver);
          frameCounter = 0;
        }
      }


    static Timer timer(5000); // tworzymy timer i ustawiamy go na 5 sekund
    if (timer.isReady())       // sprawdzamy czy już minęło 5 sek
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
      EndDrawing();
    break;
    
    default:
      std::cout << "INVALID GAME STATE" << std::endl;
    break;
    }

  }
  // CLEANUP
  UnloadTexture(snakeSprite);
  UnloadTexture(monkeySprite);
  UnloadTexture(fruitSprite);
  UnloadTexture(groundTile);
  UnloadTexture(fenceSprite);
  UnloadTexture(fenceSprite_side);
  UnloadTexture(fenceSprite_side_rotated);
  StopSoundMulti();
  UnloadSound(BCS);
  UnloadSound(GameOver);
  UnloadMusicStream(IGS);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}

