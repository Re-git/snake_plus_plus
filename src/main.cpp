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
#include "timer.h"
#include "gui.h"
#include "monkey.h"
#include "snake.h"
#include "Fruits.h"
#include "Nukes.h"
#include "Explosion.h"

GameState gameState;

int main(void){
  // INITIALIZE VARIABLES
  float screenWidth = 1420;
  float screenHeight = 1000;
  Area gameArea = {40, 80, 40, 80};
  gameState = mainMenuState;
  static Timer niezjedzone(10000);
  static Timer nieuzyte(10000);
  static Timer czas_punktowy(5000);
  static int frameCounter, points;

  // CREATE WINDOW
  SetTargetFPS(60);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow((int)screenWidth, (int)screenHeight, "Snake");
  Vector2 windowPosition = {100, 100};
  SetWindowPosition(windowPosition.x, windowPosition.y);
  Image ikona = LoadImage("assets/sprites/gui/ikona3.png");
  SetWindowIcon(ikona);
  HideCursor();

  
  // LOAD TEXTURES
  #include "loadTextures.h"

  // LOAD SOUNDS
  InitAudioDevice();
  #include "loadSounds.h"
  SetMusicVolume(IGS, 0.1);

  // RANDOM NUMBERS
  srand(time(NULL));

  // CREATE GAME OBJECTS
  Snake snake(snakeSprite, 15);
  std::vector<Malpa> monkeyList;
  std::vector<Explosion> explosions;
  Fruits fruit(fruitSprite, gameArea);
  Nukes nuke(nukeSprite, gameArea);
  Gui gui;

  // MAIN LOOP
  while (!WindowShouldClose())
  {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    switch (gameState)
    {
    // IN GAME STATE
    case inGameState:
      UpdateMusicStream(IGS);
      if(!(IsMusicPlaying(IGS)))
      {
          UpdateMusicStream(IGS);
          PlayMusicStream(IGS);
      }
      frameCounter++;
      fruit.update();
      nuke.update();

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
          explosions.push_back(Explosion(explosionSprites, snake.position.x, snake.position.y, snake.tail.size()));
          std::cout << "num of explosions" <<  explosions.size() << std::endl;
          points = points + monkeyList.size();
          nuke.moveNuke();
          nieuzyte.reset();
      }


      BeginDrawing();
      ClearBackground(BLACK);
      //RYSOWANIE PODŁOGI
      for(int x=0;x<(GetScreenWidth()/128)+1;x++)
      {
        for(int y=0;y<(GetScreenHeight()/128)+1;y++)
        {
          DrawTexture(groundTile,x*128,y*128,WHITE);          
        }
      }

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
      // GORNE GUI
      gui.drawInGameGui(points, frameCounter);



      if(czas_punktowy.isReady())
      {
      points++;
      czas_punktowy.reset(); 
      }

      if(snake.checkCollisionWithEdges(snake.position,BCS)==true) PlaySoundMulti(BCS);


      for (size_t i = 0; i < explosions.size() && i < monkeyList.size(); i++){ // Check if monkeys are hit by explosion
        if(CheckCollisionCircleRec(explosions[i].position,explosions[i].explosionSize,monkeyList[i].monkeyRec)){
          monkeyList[i].dead = 1;
        }
      }
      
      for (size_t i=0; i<monkeyList.size(); i++)  
      {
        if (monkeyList[i].dead) 
        {
          monkeyList.erase(monkeyList.begin() + i); // Remove dead monkeys
        }
        
        monkeyList[i].applyBehaviors(monkeyList, snake.position);
        monkeyList[i].update();

        if (snake.collide(monkeyList[i].monkeyRec)) 
        {
          gameState = deathScreenState;
          PlaySound(GameOver);
        }
      }

    static Timer timer(5000); 
    if (timer.isReady())       
      {
          monkeyList.push_back(Malpa(monkeySprite));
          if (timer.getLimit() > 200)
          {
            timer.setLimit(timer.getLimit() - 1);
          }   
          timer.reset();        
      }

      snake.handleInput();
      snake.update();
      snake.draw();
      fruit.draw();
      nuke.draw();
      for (size_t i = 0; i < explosions.size(); i++)
      {
        explosions[i].draw();
        explosions[i].update();
        if (explosions[i].finished)
        {
          explosions.erase(explosions.begin()+i);
        }
      }      
      EndDrawing();
    break;
    
    // MAIN MENU STATE
    case mainMenuState:
      // KEYBOARD INPUT
      if (IsKeyDown(KEY_ENTER)){
        niezjedzone.reset();
        czas_punktowy.reset();
        gameState = inGameState;
      }
      gui.checkCollisionsMainMenu(gameState);
      gui.drawMainMenu();
    break;

    // DEATH SCREEN STATE
    case deathScreenState:
      // CLEANUP
      StopMusicStream(IGS);
      monkeyList.clear();
      snake = Snake(snakeSprite, 15);
      fruit.moveFruit();
      nuke.moveNuke();
      // DRAWING
      gui.drawDeathMenu(points, frameCounter, gameState);
      // KEYBOARD INPUT
        if (IsKeyDown(KEY_ENTER)){
          gameState = inGameState;
          niezjedzone.reset();
          czas_punktowy.reset();
          points = 0;
          frameCounter = 0;
          }
    break;


    case quitState:
    // CLEANUP
    UnloadTexture(snakeSprite);
    UnloadTexture(monkeySprite);
    UnloadTexture(fruitSprite);
    UnloadTexture(nukeSprite);
    UnloadTexture(explosionSprites[1]);
    UnloadTexture(explosionSprites[2]);
    UnloadTexture(explosionSprites[3]);
    UnloadTexture(explosionSprites[4]);
    UnloadTexture(groundTile);
    UnloadTexture(fenceSprite);
    UnloadTexture(fenceSprite_side);
    UnloadTexture(fenceSprite_side_rotated);
    UnloadImage(ikona);
    StopSoundMulti();
    UnloadSound(BCS);
    UnloadSound(GameOver);
    UnloadMusicStream(IGS);
    CloseAudioDevice();
    CloseWindow();
    exit(1);
    break;

    default:
      std::cout << "INVALID GAME STATE" << std::endl;
    break;
    }
  }
  return 0;
}
