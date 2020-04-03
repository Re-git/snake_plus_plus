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
  Vector2 mousePosition = {0.0f,0.0f};

  // CREATE WINDOW
  SetTargetFPS(60);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow((int)screenWidth, (int)screenHeight, "Snake");
  Vector2 windowPosition = {100, 100};
  SetWindowPosition(windowPosition.x, windowPosition.y);
  Image ikona = LoadImage("assets/sprites/gui/ikona3.png");
  SetWindowIcon(ikona);
  
  // LOAD TEXTURES
  #include "loadTextures.h"

  // LOAD SOUNDS
  InitAudioDevice();
  #include "loadSounds.h"
  SetMusicVolume(IGS, 0.1);

  // START RANDOM NUMBER GENERATOR
  srand(time(NULL));

  // CREATE GAME OBJECTS
  Snake snake(snakeSprite, 15);
  std::vector<Malpa> monkeyList;
  std::vector<Explosion> explosions;
  Fruits fruit(fruitSprite, gameArea);
  Nukes nuke(nukeSprite, gameArea);

  // MAIN LOOP
  while (!WindowShouldClose())
  {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    mousePosition = GetMousePosition();
    Rectangle btnBounds_start = {static_cast<float>(screenWidth/2)-static_cast<float>(startButton.width/2),
                                                    static_cast<float>(screenHeight/2)-static_cast<float>(startButton.height/2),
                                                    static_cast<float>(startButton.width),static_cast<float>(startButton.height)};
    float quit_btn_y_offset = 125;
    Rectangle btnBounds_quit = {static_cast<float>(screenWidth/2)-static_cast<float>(quitButton.width/2),
                                                    static_cast<float>(screenHeight/2)-static_cast<float>(quitButton.height/2)+quit_btn_y_offset,
                                                    static_cast<float>(quitButton.width),static_cast<float>(quitButton.height)};
    float replay_btn_y_offset = 210;
    Rectangle btnBounds_replay = {static_cast<float>(screenWidth/2)-static_cast<float>(replayButton.width),
                                                       static_cast<float>(screenHeight/2)-static_cast<float>(replayButton.height/2)+replay_btn_y_offset,
                                                       static_cast<float>(replayButton.width),static_cast<float>(replayButton.height)};
    float back_btn_x_offset = 150;
    float back_btn_y_offset = 210;
    Rectangle btnBounds_back = {static_cast<float>(screenWidth/2)-static_cast<float>(backButton.width/2)+back_btn_x_offset,
                                                     static_cast<float>(screenHeight/2)-static_cast<float>(backButton.height/2)+back_btn_y_offset,
                                                     static_cast<float>(backButton.width),static_cast<float>(backButton.height)};

    switch (gameState)
    {
    case mainMenu:
     HideCursor();
      // KEYBOARD INPUT
      if (IsKeyDown(KEY_ENTER)){
        niezjedzone.reset();
        czas_punktowy.reset();
        gameState = inGame;
      }
      // DRAWING  
      BeginDrawing();
      ClearBackground(GREEN);

      if(IsWindowResized()) 
      {
        menuBackground = GenImageChecked(GetScreenWidth(), GetScreenHeight(),3,10,BLACK,DARKGREEN);
        menuBG = LoadTextureFromImage(menuBackground);
      }

      if(IsKeyPressed(KEY_LEFT_SHIFT))
      {
      menuBackground = GenImageChecked(GetScreenWidth(), GetScreenHeight(), GetRandomValue(0,100), GetRandomValue(0,100), Color{static_cast<unsigned char>(GetRandomValue(0,120)),static_cast<unsigned char>(GetRandomValue(0,255)),static_cast<unsigned char>(GetRandomValue(0,120)),150},Color{static_cast<unsigned char>(GetRandomValue(0,255)),static_cast<unsigned char>(GetRandomValue(0,120)),static_cast<unsigned char>(GetRandomValue(0,100)),150});
      menuBG = LoadTextureFromImage(menuBackground);
      }
      DrawTexture(menuBG,0,0,WHITE);
      DrawTextureEx(menuLogo,Vector2{screenWidth/2-menuLogo.width/2,screenHeight/2-menuLogo.height-100},0,1,WHITE);
      DrawTextureEx(startButton,Vector2{screenWidth/2-startButton.width/2,screenHeight/2-startButton.height/2},0,1,WHITE);
      DrawTextureEx(quitButton,Vector2{screenWidth/2-quitButton.width/2,screenHeight/2-quitButton.height/2+quit_btn_y_offset},0,1,WHITE);
      DrawTexture(kursor,mousePosition.x,mousePosition.y,WHITE);
    
      if(CheckCollisionPointRec(mousePosition ,btnBounds_start))
      {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
          PlaySound(klikniecie);
          gameState = inGame; 
        }
      }

      if(CheckCollisionPointRec(mousePosition ,btnBounds_quit))
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
        DrawTexture(menuBG,0,0,WHITE);
        DrawTexture(scorebox,(GetScreenWidth()/2)-scorebox.width/2,(GetScreenHeight()/2)-50-scorebox.height/2,WHITE);
        DrawTextureEx(replayButton,Vector2{btnBounds_replay.x,btnBounds_replay.y},0,1,WHITE);
        DrawTextureEx(backButton,Vector2{btnBounds_back.x,btnBounds_back.y},0,1,WHITE);

        if(CheckCollisionPointRec(mousePosition, btnBounds_replay))
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
  
        if(CheckCollisionPointRec(mousePosition, btnBounds_back))
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
        mousePosition = GetMousePosition();
        DrawTexture(kursor,mousePosition.x,mousePosition.y,WHITE);
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

          // monkeyList.clear();
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

      for (size_t i=0; i<monkeyList.size(); i++)  // for every monkey in monkey list
      {
        if (monkeyList[i].dead)
        {
          monkeyList.erase(monkeyList.begin() + i);
        }
        
        monkeyList[i].applyBehaviors(monkeyList, snake.position);
        monkeyList[i].update();
        if (snake.collide(monkeyList[i].monkeyRec)) 
        {
          gameState = deathScreen;
          PlaySound(GameOver);
        }
        for (size_t i = 0; i < explosions.size(); i++){
          if(CheckCollisionCircleRec(explosions[i].position,explosions[i].explosionSize,monkeyList[i].monkeyRec)){
            monkeyList[i].dead = 1;
          }
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
