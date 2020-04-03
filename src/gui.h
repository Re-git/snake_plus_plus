#pragma once

#include "libs/raylib.h"
#include "libs/raymath.h"
#include "utility.h"

class Gui
{
private:
    Texture2D startButton = LoadTexture("assets/sprites/gui/start4.png");
    Texture2D quitButton = LoadTexture("assets/sprites/gui/quit3.png");
    Texture2D replayButton = LoadTexture("assets/sprites/gui/replay_small.png");
    Texture2D scorebox = LoadTexture("assets/sprites/gui/scorebox.png");
    Texture2D kursor = LoadTexture("assets/sprites/gui/cursor.png");
    Texture2D menuLogo = LoadTexture("assets/sprites/gui/logo3_small.png");
    Texture2D backButton = LoadTexture("assets/sprites/gui/menu3.png");
    Sound klikniecie = LoadSound("assets/sounds/toggle_001.ogg");
    Image menuBackground = GenImageChecked(GetScreenWidth(), GetScreenHeight(),3,10,BLACK,DARKGREEN);
    Texture2D menuBG = LoadTextureFromImage(menuBackground);
    float quit_btn_y_offset = 125;
public:
    Gui();
    ~Gui();
    void checkCollisionsMainMenu(GameState&);
    void drawMainMenu();
    void drawDeathMenu(int points, int frameCounter, GameState& gameState);
    void drawInGameGui(int points, int frameCounter);
};


Gui::Gui()
{
}


Gui::~Gui()
{
    UnloadTexture(startButton);
    UnloadTexture(quitButton);
    UnloadTexture(menuLogo);
    UnloadTexture(menuBG);
    UnloadTexture(kursor);
    UnloadTexture(replayButton);
    UnloadTexture(backButton);
    UnloadImage(menuBackground);
    UnloadSound(klikniecie);
}


void Gui::drawMainMenu()
{
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

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
    DrawTexture(kursor,GetMouseX(),GetMouseY(),WHITE);
    EndDrawing();
}


void Gui::checkCollisionsMainMenu(GameState& gameState)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Rectangle btnBounds_start = {static_cast<float>(screenWidth/2)-static_cast<float>(startButton.width/2),
                                                    static_cast<float>(screenHeight/2)-static_cast<float>(startButton.height/2),
                                                    static_cast<float>(startButton.width),static_cast<float>(startButton.height)};
    Rectangle btnBounds_quit = {static_cast<float>(screenWidth/2)-static_cast<float>(quitButton.width/2),
                                                    static_cast<float>(screenHeight/2)-static_cast<float>(quitButton.height/2)+quit_btn_y_offset,
                                                    static_cast<float>(quitButton.width),static_cast<float>(quitButton.height)};
    if(CheckCollisionPointRec(GetMousePosition() ,btnBounds_start))
    {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            PlaySound(klikniecie);
            gameState = GameState::inGameState; 
        }
    }

    if(CheckCollisionPointRec(GetMousePosition() ,btnBounds_quit))
    {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            PlaySound(klikniecie);
            gameState = quitState;
        }
    }
}


void Gui::drawDeathMenu(int points, int frameCounter, GameState& gameState)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float replay_btn_y_offset = 210;
    Rectangle btnBounds_replay = {static_cast<float>(screenWidth/2)-static_cast<float>(replayButton.width),
                                                       static_cast<float>(screenHeight/2)-static_cast<float>(replayButton.height/2)+replay_btn_y_offset,
                                                       static_cast<float>(replayButton.width),static_cast<float>(replayButton.height)};
    float back_btn_x_offset = 150;
    float back_btn_y_offset = 210;
    Rectangle btnBounds_back = {static_cast<float>(screenWidth/2)-static_cast<float>(backButton.width/2)+back_btn_x_offset,
                                                     static_cast<float>(screenHeight/2)-static_cast<float>(backButton.height/2)+back_btn_y_offset,
                                                     static_cast<float>(backButton.width),static_cast<float>(backButton.height)};

        BeginDrawing();
        ClearBackground(GREEN);
        DrawTexture(menuBG,0,0,WHITE);
        DrawTexture(scorebox,(GetScreenWidth()/2)-scorebox.width/2,(GetScreenHeight()/2)-50-scorebox.height/2,WHITE);
        DrawTextureEx(replayButton,Vector2{btnBounds_replay.x,btnBounds_replay.y},0,1,WHITE);
        DrawTextureEx(backButton,Vector2{btnBounds_back.x,btnBounds_back.y},0,1,WHITE);

        if(CheckCollisionPointRec(GetMousePosition(), btnBounds_replay))
      {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
        //   niezjedzone.reset();
        //   czas_punktowy.reset();
        //   points = 0;
        //   frameCounter = 0;
          PlaySound(klikniecie);
          gameState = inGameState; 
        }
      }
  
    if(CheckCollisionPointRec(GetMousePosition(), btnBounds_back))
      {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
        //   niezjedzone.reset();
        //   czas_punktowy.reset();
        //   points = 0;
        //   frameCounter = 0;
          PlaySound(klikniecie);
          gameState = mainMenuState;
        }
      }

        if(IsWindowResized()) 
      {
        menuBackground = GenImageChecked(GetScreenWidth(), GetScreenHeight(),3,10,BLACK,DARKGREEN);
        menuBG = LoadTextureFromImage(menuBackground);
      }

        DrawText(TextFormat("YOUR SCORE: %d", points),85+GetScreenWidth()/2 -scorebox.width/2,170+GetScreenHeight()/2-scorebox.height/2, 50,BLACK);
        DrawText(TextFormat("TIME SURVIVED: %ds", frameCounter/60),30+(GetScreenWidth()/2)-scorebox.width/2,120+GetScreenHeight()/2-scorebox.height/2, 50,BLACK);
        DrawTexture(kursor,GetMouseX(),GetMouseY(),WHITE);
        EndDrawing();
}

void Gui::drawInGameGui(int points, int frameCounter)
{
    int screenWidth = GetScreenWidth();
    // int screenHeight = GetScreenHeight();
    //GÓRNA CZĘŚĆ GUI
      DrawRectangle(0,0,screenWidth,60, Color{8,8,8,133});
      DrawText(TextFormat("PUNKTY: %d",points),30,15,35,RAYWHITE);
      DrawText(TextFormat("CZAS: %d",frameCounter/60),screenWidth-200,15,35,RAYWHITE);
}