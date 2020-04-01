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
  Area gameArea = {40, 80, 40, 80};
  gameState = mainMenu;
  static Timer niezjedzone(10000);
  static Timer nieuzyte(10000);
  static Timer czas_punktowy(5000);      //5 sekund czasu gry
  static int frameCounter, points;
  // int text_size;
  InitAudioDevice();
    // CREATE WINDOW
  SetTargetFPS(60);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow((int)screenWidth, (int)screenHeight, "Snake");
  Vector2 windowPosition = {100, 100};
  SetWindowPosition(windowPosition.x, windowPosition.y);
  Image ikona = LoadImage("assets/sprites/gui/ikona3.png");
  SetWindowIcon(ikona);
  
  // START RANDOM NUMBER GENERATOR
  srand(time(NULL));
  // LOAD TEXTURES
  Texture2D fruitSprite = LoadTexture("assets/sprites/food/owocek.png");
  Texture2D monkeySprite = LoadTexture("assets/sprites/enemies/monkey.png");
  Texture2D snakeSprite = LoadTexture("assets/sprites/character/snake.png");
  Texture2D nukeSprite = LoadTexture("assets/sprites/powerups/3.png");
  Texture2D explosionSprites[4];
  explosionSprites[0] = LoadTexture("assets/sprites/effects/explosion1.png");
  explosionSprites[1] = LoadTexture("assets/sprites/effects/explosion2.png");
  explosionSprites[2] = LoadTexture("assets/sprites/effects/explosion3.png");
  explosionSprites[3] = LoadTexture("assets/sprites/effects/explosion4.png");
  Texture2D groundTile = LoadTexture("assets/sprites/tiles/Ground_Tile_01_B.png");
  Texture2D fenceSprite = LoadTexture("assets/sprites/tiles/bush_pionowy.png");
  Texture2D fenceSprite_side = LoadTexture("assets/sprites/tiles/bush_poziomy.png");
  Texture2D fenceSprite_side_rotated = LoadTexture("assets//sprites/tiles/bush_poziomy_odbity.png");
  Texture2D startButton = LoadTexture("assets/sprites/gui/start4.png");
  Texture2D quitButton = LoadTexture("assets/sprites/gui/quit3.png");
  Texture2D replayButton = LoadTexture("assets/sprites/gui/replay_small.png");
  Sound BCS = LoadSound("assets/sounds/phaseJump1.ogg");  //BCS-BorderCollisionSound
  Music IGS = LoadMusicStream("assets/soundtrack/neogauge.mp3"); //IGS-InGameSoundtrack
  Sound GameOver= LoadSound("assets/voiceOver/game_over.ogg");
  Sound klikniecie = LoadSound("assets/sounds/toggle_001.ogg");
  Rectangle sourceRec_start = {0.0f,0.0f,static_cast<float>(startButton.width),static_cast<float>(startButton.height)};
  Rectangle btnBounds_start = {static_cast<float>(GetScreenWidth()/2)-static_cast<float>(startButton.width/2),static_cast<float>(GetScreenHeight()/2)-static_cast<float>(startButton.height/2),static_cast<float>(startButton.width),static_cast<float>(startButton.height)};
  Rectangle sourceRec_quit = {0.0f,0.0f,static_cast<float>(quitButton.width),static_cast<float>(quitButton.height)};
  Rectangle btnBounds_quit = {static_cast<float>(GetScreenWidth()/2)-static_cast<float>(quitButton.width/2),static_cast<float>(GetScreenHeight()/2)-static_cast<float>(quitButton.height/2),static_cast<float>(quitButton.width),static_cast<float>(quitButton.height)};
  Rectangle sourceRec_replay = {0.0f,0.0f,static_cast<float>(replayButton.width),static_cast<float>(replayButton.height)};
  Rectangle btnBounds_replay = {static_cast<float>(GetScreenWidth()/2)-static_cast<float>(replayButton.width/2),static_cast<float>(GetScreenHeight()/2)-static_cast<float>(replayButton.height/2),static_cast<float>(replayButton.width),static_cast<float>(replayButton.height)};
  Texture2D scorebox = LoadTexture("assets/sprites/gui/scorebox.png");
  Vector2 mousePoint = {0.0f,0.0f};
  Texture2D kursor = LoadTexture("assets/sprites/gui/cursor.png");
  Texture2D menuLogo = LoadTexture("assets/sprites/gui/logo3_small.png");
  Texture2D backButton = LoadTexture("assets/sprites/gui/menu3.png");
  Image menuBackground = GenImageChecked(GetScreenWidth(), GetScreenHeight(),3,10,BLACK,DARKGREEN);
  Texture2D menuBG = LoadTextureFromImage(menuBackground);
  Rectangle sourceRec_back = {0.0f,0.0f,static_cast<float>(backButton.width),static_cast<float>(backButton.height)};
  Rectangle btnBounds_back = {static_cast<float>(GetScreenWidth()/2)-static_cast<float>(backButton.width/2),static_cast<float>(GetScreenHeight()/2)-static_cast<float>(backButton.height/2),static_cast<float>(backButton.width),static_cast<float>(backButton.height)};

  SetMusicVolume(IGS, 0.2);

  // CREATE GAME OBJECTS
  Snake snake(snakeSprite, 15);
  std::vector<Malpa> monkeyList;
  std::vector<Explosion> explosions;
  Fruits fruit(fruitSprite, gameArea);
  Nukes nuke(nukeSprite, gameArea);

 
 

  // To jest główna pętla, wykonywana dopóki okno nie zostanie zamknięte
  while (!WindowShouldClose())
  {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    switch (gameState)
    {
    case mainMenu:
    HideCursor();

      // KEYBOARD INPUT
      if (IsKeyDown(KEY_ENTER)){
        gameState = inGame;
        niezjedzone.reset();
        czas_punktowy.reset();}
      // DRAWING  
      BeginDrawing();
      ClearBackground(GREEN);

      if(IsWindowResized()) 
      {
        menuBackground = GenImageChecked(GetScreenWidth(), GetScreenHeight(),3,10,BLACK,DARKGREEN);
        menuBG = LoadTextureFromImage(menuBackground);
      }

      if(CheckCollisionPointRec(mousePoint,Rectangle{0.0f,0.0f,static_cast<float>(GetScreenWidth()),static_cast<float>(GetScreenHeight())}))
      {
        if(IsKeyPressed(KEY_LEFT_SHIFT))
        {
        menuBackground = GenImageChecked(GetScreenWidth(), GetScreenHeight(), GetRandomValue(0,100), GetRandomValue(0,100), Color{static_cast<unsigned char>(GetRandomValue(0,120)),static_cast<unsigned char>(GetRandomValue(0,255)),static_cast<unsigned char>(GetRandomValue(0,120)),150},Color{static_cast<unsigned char>(GetRandomValue(0,255)),static_cast<unsigned char>(GetRandomValue(0,120)),static_cast<unsigned char>(GetRandomValue(0,100)),150});
        menuBG = LoadTextureFromImage(menuBackground);
        }
      }
      mousePoint = GetMousePosition();
      DrawTexture(menuBG,0,0,WHITE);
      DrawTexture(menuLogo,GetScreenWidth()/2.0-menuLogo.width/2,GetScreenHeight()/2.0-menuLogo.height-100,WHITE);
      btnBounds_start.x = static_cast<float>(GetScreenWidth()/2-startButton.width/2);
      btnBounds_start.y = static_cast<float>(GetScreenHeight()/2-startButton.height/2);
      btnBounds_quit.x = static_cast<float>(GetScreenWidth()/2-quitButton.width/2);
      btnBounds_quit.y = static_cast<float>(GetScreenHeight()/2-quitButton.height/2)+125;
      DrawTextureRec(startButton,sourceRec_start,Vector2{btnBounds_start.x,btnBounds_start.y},WHITE);
      DrawTextureRec(quitButton,sourceRec_quit,Vector2{btnBounds_quit.x,btnBounds_quit.y},WHITE);
      DrawTexture(kursor,mousePoint.x,mousePoint.y,WHITE);
    
      if(CheckCollisionPointRec(mousePoint,btnBounds_start))
      {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
          PlaySound(klikniecie);
        gameState = inGame; 
        }
      }

      if(CheckCollisionPointRec(mousePoint,btnBounds_quit))
      {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
          PlaySound(klikniecie);
          goto sprzataczka;
        }
      }

      EndDrawing();
    break;

    case deathScreen:
      // CLEANUP
      StopMusicStream(IGS);
      monkeyList.clear();
      snake = Snake(snakeSprite, 15);
      fruit.moveFruit();
      nuke.moveNuke();


      // DRAWING
        BeginDrawing();
        ClearBackground(GREEN);
        btnBounds_replay.x = static_cast<float>(GetScreenWidth()/2-replayButton.width/2)-replayButton.width/2;
        btnBounds_replay.y = static_cast<float>(GetScreenHeight()/2-replayButton.height/2)+210;
        btnBounds_back.x = static_cast<float>(GetScreenWidth()/2-backButton.width/2)+150;
        btnBounds_back.y = static_cast<float>(GetScreenHeight()/2-backButton.height/2)+210;
        DrawTexture(menuBG,0,0,WHITE);
        DrawTexture(scorebox,(GetScreenWidth()/2)-scorebox.width/2,(GetScreenHeight()/2)-50-scorebox.height/2,WHITE);
        DrawTextureRec(replayButton,sourceRec_replay,Vector2{btnBounds_replay.x,btnBounds_replay.y},WHITE);
        DrawTextureRec(backButton,sourceRec_back,Vector2{btnBounds_back.x,btnBounds_back.y},WHITE);

        if(CheckCollisionPointRec(mousePoint,btnBounds_replay))
      {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
          niezjedzone.reset();
          czas_punktowy.reset();
          points = 0;
          frameCounter = 0;
          PlaySound(klikniecie);
          gameState = inGame; 
        }
      }
  
        if(CheckCollisionPointRec(mousePoint,btnBounds_back))
      {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
          niezjedzone.reset();
          czas_punktowy.reset();
          points = 0;
          frameCounter = 0;
          PlaySound(klikniecie);
          gameState = mainMenu;
        }
      }

        if(IsWindowResized()) 
      {
        menuBackground = GenImageChecked(GetScreenWidth(), GetScreenHeight(),3,10,BLACK,DARKGREEN);
        menuBG = LoadTextureFromImage(menuBackground);
      }

        DrawText(TextFormat("YOUR SCORE: %d", points),85+GetScreenWidth()/2 -scorebox.width/2,170+GetScreenHeight()/2-scorebox.height/2, 50,BLACK);
        DrawText(TextFormat("TIME SURVIVED: %ds", frameCounter/60),30+(GetScreenWidth()/2)-scorebox.width/2,120+GetScreenHeight()/2-scorebox.height/2, 50,BLACK);
        mousePoint = GetMousePosition();
        DrawTexture(kursor,mousePoint.x,mousePoint.y,WHITE);
        EndDrawing();
      // KEYBOARD INPUT
        if (IsKeyDown(KEY_ENTER)){
          gameState = inGame;
          niezjedzone.reset();
          czas_punktowy.reset();
          points = 0;
          frameCounter = 0;
          }

    break;

    case inGame:

      UpdateMusicStream(IGS);
      if(!(IsMusicPlaying(IGS)))
      {
          UpdateMusicStream(IGS);
          PlayMusicStream(IGS);
      }
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
                explosions.push_back(Explosion(explosionSprites, snake.position.x, snake.position.y));
                std::cout << "num of explosions" <<  explosions.size() << std::endl;
                points = points + monkeyList.size();
                monkeyList.clear();
                nuke.moveNuke();
                nieuzyte.reset();
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
      if(snake.checkCollisionWithEdges(snake.position,BCS)==true) PlaySoundMulti(BCS);

      for (Malpa &m : monkeyList)  // for every monkey in monkey list
      {
        m.applyBehaviors(monkeyList, snake.position);
        m.update();
        if (snake.collide(m.monkeyRec)) 
        {
          gameState = deathScreen;
          PlaySound(GameOver);
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
      nuke.draw();r
      for (Explosion ex : explosions)
      {
        ex.update();
        ex.draw();
      }      
      EndDrawing();
    break;
    
    default:
      std::cout << "INVALID GAME STATE" << std::endl;
    break;
    }

  }
  // CLEANUP
  sprzataczka:
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
  UnloadTexture(startButton);
  UnloadTexture(quitButton);
  UnloadTexture(menuLogo);
  UnloadTexture(menuBG);
  UnloadTexture(kursor);
  UnloadTexture(replayButton);
  UnloadTexture(backButton);
  UnloadImage(menuBackground);
  UnloadImage(ikona);
  StopSoundMulti();
  UnloadSound(BCS);
  UnloadSound(GameOver);
  UnloadSound(klikniecie);
  UnloadMusicStream(IGS);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}

