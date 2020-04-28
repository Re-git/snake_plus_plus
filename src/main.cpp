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
#include "BulletTime.h"
#include "FrostExplosion.h"
#include "FrostNuke.h"
#include "pig.h"

GameState gameState;

int main(void){
  // INITIALIZE VARIABLES
  float screenWidth = 1420;
  float screenHeight = 1000;
  float wkurwiacz = 1.5;
  Area gameArea = {45, 85, 45, 85};
  gameState = mainMenuState;
  int pigToken = 0;
  int aktualny_poziom = 0;
 
  // static Timer nieuzyte(10000);         // nieużyty timer nieużyte >.<
  static Timer frozenTimer(5000);
  static Timer czas_punktowy(5000);     // RESPAWN OWOCKA
  static Timer czas_trudnosci(100000);   // ZMIANA TILESA
  static int frameCounter, points, rodzaj;

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
Texture2D fruitSprite = LoadTexture("assets/sprites/food/owocek.png");
Texture2D monkeySprite = LoadTexture("assets/sprites/enemies/malpa_angry.png");
Texture2D pigSprite = LoadTexture("assets/sprites/enemies/pig_angry.png");
Texture2D snakeSprite = LoadTexture("assets/sprites/character/snake.png");
Texture2D nukeSprite = LoadTexture("assets/sprites/powerups/3.png");
Texture2D explosionSprites[5];
explosionSprites[0] = LoadTexture("assets/sprites/effects/explosion1.png");
explosionSprites[1] = LoadTexture("assets/sprites/effects/explosion2.png");
explosionSprites[2] = LoadTexture("assets/sprites/effects/explosion3.png");
explosionSprites[3] = LoadTexture("assets/sprites/effects/explosion4.png");
explosionSprites[4] = LoadTexture("assets/sprites/effects/explosion5.png");

Texture2D frostNukeSprite = LoadTexture("assets/sprites/powerups/potion.png");
Texture2D frostExplosionSprites[5];
frostExplosionSprites[0] = LoadTexture("assets/sprites/effects/explosion1.png");
frostExplosionSprites[1] = LoadTexture("assets/sprites/effects/frostExplosion2.png");
frostExplosionSprites[2] = LoadTexture("assets/sprites/effects/frostExplosion3.png");
frostExplosionSprites[3] = LoadTexture("assets/sprites/effects/frostExplosion4.png");
frostExplosionSprites[4] = LoadTexture("assets/sprites/effects/frostExplosion5.png");
Texture2D groundTiles[10] = {LoadTexture("assets/sprites/tiles/Ground_Tile_01_B.png"), LoadTexture("assets/sprites/tiles/poziomy/stone.jpg"),LoadTexture("assets/sprites/tiles/poziomy/Ground_Tile_02_C.png"),LoadTexture("assets/sprites/tiles/poziomy/tile_stoneSlabs.png"),LoadTexture("assets/sprites/tiles/poziomy/cegly.jpg"),LoadTexture("assets/sprites/tiles/poziomy/sand.jpg"), LoadTexture("assets/sprites/tiles/poziomy/snow.jpg"), LoadTexture("assets/sprites/tiles/poziomy/marble.jpg"), LoadTexture("assets/sprites/tiles/poziomy/water2.png"), LoadTexture("assets/sprites/tiles/poziomy/magma.jpg")};
  
Texture2D fenceSprite = LoadTexture("assets/sprites/tiles/bush_pionowy.png");
Texture2D fenceSprite_side = LoadTexture("assets/sprites/tiles/bush_poziomy.png");
Texture2D fenceSprite_side_rotated = LoadTexture("assets//sprites/tiles/bush_poziomy_odbity.png");
Texture2D bulletTimeSprite[2] = {LoadTexture("assets/sprites/powerups/redpill2.png"),LoadTexture("assets/sprites/powerups/bluepill2.png")};

  // LOAD SOUNDS
  InitAudioDevice();
  Sound Bomb = LoadSound("assets/sounds/Bomb.mp3");
  Sound frostBomb = LoadSound("assets/sounds/laser4.ogg");
  Sound bulletIn = LoadSound("assets/sounds/bullet_in.wav");
  Sound bulletOut = LoadSound("assets/sounds/bullet_out.wav");
  Sound Wre = LoadSound("assets/sounds/wreee.wav");
  Sound Eat = LoadSound("assets/sounds/eat.mp3");
  Sound BCS = LoadSound("assets/sounds/phaseJump1.ogg");  //BCS-BorderCollisionSound
  Music IGS = LoadMusicStream("assets/soundtrack/if_you_dont_love_me.mp3"); //IGS-InGameSoundtrack
  Music IGD = LoadMusicStream("assets/soundtrack/Cyberpunk_Moonlight_Sonata_v2.mp3"); //IGS-InGameSoundtrack
  Music IGM = LoadMusicStream("assets/soundtrack/neogauge.mp3"); //IGS-InGameSoundtrack
  Sound GameOver= LoadSound("assets/voiceOver/game_over.ogg");
  SetMusicVolume(IGS, 0.2);
  SetMusicVolume(IGD, 0.1);
  SetMusicVolume(IGM, 0.1);

  // RANDOM NUMBERS
  srand(time(NULL));

  // CREATE GAME OBJECTS
  Snake snake(snakeSprite, 15);
  std::vector<Malpa> monkeyList;
  std::vector<Pig> pigList;
  std::vector<Explosion> explosions;
  std::vector<FrostExplosion> frostExplosion;
  FrostNuke frostNuke(frostNukeSprite, gameArea);
  Fruit fruit(fruitSprite, gameArea);
  Bullet bullet(bulletTimeSprite, gameArea);
  Nuke nuke(nukeSprite, gameArea);
  Gui gui;

  // MAIN LOOP
  while (!WindowShouldClose()) {
      screenWidth = GetScreenWidth();
      screenHeight = GetScreenHeight();
      switch (gameState) {
          // IN GAME STATE
          case inGameState:
              StopMusicStream(IGD);
              StopMusicStream(IGM);
              UpdateMusicStream(IGS);
              if (!(IsMusicPlaying(IGS))) {
                  UpdateMusicStream(IGS);
                  PlayMusicStream(IGS);
              }
              frameCounter++;
              if (snake.collide(nuke.collisionMask)) {
                  explosions.emplace_back(
                          Explosion(explosionSprites, snake.position.x, snake.position.y, snake.tail.size()));
                  // std::cout << "num of explosions" <<  explosions.size() << std::endl;
                  points = points + monkeyList.size();
                  nuke.moveNukeOutside();
                  nuke.outsideTimer->reset();
                  nuke.respawnTimer->reset();
                  PlaySoundMulti(Bomb);
              }
              if (snake.collide(frostNuke.collisionMask)) {
                  frostExplosion.push_back(
                          FrostExplosion(frostExplosionSprites, snake.position.x, snake.position.y, snake.tail.size()));
                  std::cout << "num of frostExplosions" << frostExplosion.size() << std::endl;
                  points = points + monkeyList.size();
                  frostNuke.moveFrostNukeOutside();
                  frostNuke.respawnTimer->reset();
                  frostNuke.outsideTimer->reset();
                  PlaySoundMulti(frostBomb);
              }

              BeginDrawing();
              ClearBackground(BLACK);
              //RYSOWANIE PODŁOGI

              for (int x = 0; x < (GetScreenWidth() / 128) + 1; x++) {
                  for (int y = 0; y < (GetScreenHeight() / 128) + 1; y++) {
                      DrawTexture(groundTiles[rodzaj], x * 128, y * 128, WHITE);
                  }
              }

              if (czas_trudnosci.isReady()) {
                  rodzaj++;
                  czas_trudnosci.reset();
              }


              //RYSOWANIE RAMECZKI - BUSH
              for (int x = 0; x < (GetScreenWidth() + 1); x = x + 127) {
                  DrawTexture(fenceSprite_side, x, 58, WHITE);
                  DrawTexture(fenceSprite_side_rotated, x, GetScreenHeight() - 50, WHITE);
              }
              for (int y = 60; y < (GetScreenHeight() - 44); y = y + 70) {
                  DrawTexture(fenceSprite, 0, y, WHITE);
                  DrawTexture(fenceSprite, GetScreenWidth() - 40, y, WHITE);
              }
              // GORNE GUI
              gui.drawInGameGui(points, frameCounter);

              if (czas_punktowy.isReady()) {
                  points++;
                  czas_punktowy.reset();
              }

              if (snake.checkCollisionWithEdges(snake.position, BCS) == true) { PlaySoundMulti(BCS); }


              for (size_t i = 0; i < monkeyList.size(); i++) { // Check if monkeys are hit by explosion
                  for (size_t j = 0; j < explosions.size(); j++) {
                      for (size_t k = 0; k < pigList.size(); k++) {
                          if (CheckCollisionCircleRec(explosions[j].position, explosions[j].explosionSize,
                                                      monkeyList[i].monkeyRec)) {
                              monkeyList[i].dead = 1;
                          }
                          if (CheckCollisionCircleRec(explosions[j].position, explosions[j].explosionSize,
                                                      pigList[k].pigRec)) {
                              pigToken = 0;
                              pigList.clear();
                          }
                      }
                  }
              }

                          // WARUNEK ZMIANY TRUDNOŚCI - CO 100PKT
        
                          if (points > 99 + aktualny_poziom && points < 99 + aktualny_poziom + 12) {
                              aktualny_poziom += 100;
                              wkurwiacz += 0.25;
                            // std::cout << "ZWIEKSZONO POZIOM - " << aktualny_poziom << " " << wkurwiacz << std::endl;
                          }

                          if (points < 99) {
                              aktualny_poziom = 0;
                              wkurwiacz = 1.5;
                          }

              for (size_t i = 0; i < monkeyList.size(); i++)
                  for (size_t j = 0; j < pigList.size(); j++) {
                          if (monkeyList[i].dead) {
                              monkeyList.erase(monkeyList.begin() + i); // Remove dead monkeys
                          }


                        if(monkeyList[i].frozen==0)
                        {
                          monkeyList[i].maxspeed = wkurwiacz;
                        //   std::cout << monkeyList[i].maxspeed;
                        }

                        if(pigList[j].frozen==0)
                        {
                          pigList[j].maxspeed = wkurwiacz - 0.5;
                        }
                          if (snake.collide(monkeyList[i].monkeyRec) || snake.collide(pigList[j].pigRec)) {
                              gameState = deathScreenState;
                              PlaySound(GameOver);
                              bullet.N = 0;
                              bullet.podniesiony = 0;
                              monkeyList[i].maxspeed = 1.5;
                              bullet.penaltyValue = 0;
                              pigList[j].maxspeed = 1;
                          }
                      }
                      for (size_t i = 0; i < monkeyList.size(); i++) {
                          for (size_t j = 0; j < frostExplosion.size(); j++) {
                              if (CheckCollisionCircleRec(frostExplosion[j].position,
                                                          frostExplosion[j].frostExplosionSize,
                                                          monkeyList[i].monkeyRec)) {
                                  monkeyList[i].frozen = 1;
                                  monkeyList[i].maxspeed = 0;
                              }
                          }
                      }
                      for (size_t i = 0; i < monkeyList.size(); i++) {
                          if (monkeyList[i].frozen) {
                              if (frozenTimer.isReady()) {
                                  monkeyList[i].maxspeed = 1.5;   // freez monkeys
                                  monkeyList[i].frozen = 0;
                                 if(i==monkeyList.size()-1) frozenTimer.reset();
                              }
                          }
                          if (monkeyList[i].frozen != 1) monkeyList[i].applyBehaviors(monkeyList, snake.position);
                          monkeyList[i].update();
                      }

                      for (size_t i = 0; i < pigList.size(); i++) { // Check if pigs are hit by frostExplosion
                          for (size_t j = 0; j < frostExplosion.size(); j++) {
                              if (CheckCollisionCircleRec(frostExplosion[j].position,
                                                          frostExplosion[j].frostExplosionSize,
                                                          pigList[i].pigRec)) {
                                  pigList[i].frozen = 1;
                                  pigList[i].maxspeed = 0;
                              }
                          }
                      }

                      for (size_t i = 0; i < pigList.size(); i++) {
                          if (pigList[i].frozen) {
                              if (frozenTimer.isReady()) {
                                  pigList[i].maxspeed = 1;   // freez pigs
                                  pigList[i].frozen = 0;
                                if(i==pigList.size()-1) frozenTimer.reset();
                              }
                          }
                          if (pigList[i].frozen != 1) pigList[i].applyBehaviors(pigList, fruit.position);
                          pigList[i].update();
                      }

                      static Timer timer(3000);
                      if (timer.isReady()) {
                          monkeyList.push_back(Malpa(monkeySprite));
                          if (timer.getLimit() > 200) {
                              timer.setLimit(timer.getLimit() - 1);
                          }
                          timer.reset();
                      }
                      static Timer pig_timer(5000);
                      if (pig_timer.isReady() && pigToken != 1) {
                          pigList.push_back(Pig(pigSprite));
                          if (pig_timer.getLimit() > 200) {
                              pig_timer.setLimit(pig_timer.getLimit() - 1);
                          }
                          pig_timer.reset();
                          pigToken = 1;
                      }

                      snake.handleInput();
                      snake.update();
                      snake.draw();
                      fruit.draw(snake, pigList, points, Eat, Wre);
                      nuke.draw();
                      frostNuke.draw();
                      bullet.draw(snake, points, bulletIn, bulletOut);
                      for (size_t i = 0; i < explosions.size(); i++) {
                          explosions[i].draw();
                          explosions[i].update();
                          if (explosions[i].finished) {
                              explosions.erase(explosions.begin() + i);
                          }
                      }
                      for (size_t i = 0; i < frostExplosion.size(); i++) {
                          frostExplosion[i].draw();
                          frostExplosion[i].update();
                          if (frostExplosion[i].finished) {
                              frostExplosion.erase(frostExplosion.begin() + i);
                          }
                      }

                      EndDrawing();
                      break;

                      // MAIN MENU STATE
                      case mainMenuState: {
                            StopMusicStream(IGD);
                            UpdateMusicStream(IGM);
                            if (!(IsMusicPlaying(IGM))) {
                                UpdateMusicStream(IGM);
                                PlayMusicStream(IGM);
                            }
                          // KEYBOARD INPUT
                          if (IsKeyDown(KEY_ENTER)) {
                              czas_punktowy.reset();
                              gameState = inGameState;
                          }
                          gui.checkCollisionsMainMenu(gameState);
                          gui.drawMainMenu();
                          break;
                      }
                      // DEATH SCREEN STATE
                      case deathScreenState:
                          StopMusicStream(IGS);
                          StopMusicStream(IGM);
                          UpdateMusicStream(IGD);
                            if (!(IsMusicPlaying(IGD))) {
                                UpdateMusicStream(IGD);
                                PlayMusicStream(IGD);
                            }
                          monkeyList.clear();
                          pigList.clear();
                          snake = Snake(snakeSprite, 15);
                          fruit.moveFruit();
                          bullet.moveBulletTime();
                          nuke.moveNuke();
                          frostNuke.moveFrostNuke();
                          gui.drawDeathMenu(points, frameCounter, gameState);

                          if (IsKeyDown(KEY_ENTER)) {
                              gameState = inGameState;
                          }

                          // odupośledzenie przycisków po refactoringu - czyszczenie zmiennych przed next runda
                          if (gameState == inGameState || gameState == mainMenuState) {
                              gameState = (gameState == inGameState) ? inGameState : mainMenuState;
                              czas_punktowy.reset();
                              czas_trudnosci.reset();
                              bullet.penaltyTimer->reset();
                              pig_timer.reset();
                              wkurwiacz = 1.5;
                              points = 0;
                              pigToken = 0;
                              frameCounter = 0;
                              rodzaj = 0;
                              bullet.N = 0;
                              bullet.podniesiony = 0;
                              bullet.penaltyValue = 0;
                              SetTargetFPS(60);
                          }
                          break;


                      case quitState:
                          // CLEANUP
                          UnloadTexture(snakeSprite);
                          UnloadTexture(monkeySprite);
                          UnloadTexture(fruitSprite);
                          UnloadTexture(nukeSprite);
                          UnloadTexture(pigSprite);
                          UnloadTexture(frostNukeSprite);
                          UnloadTexture(explosionSprites[1]);
                          UnloadTexture(explosionSprites[2]);
                          UnloadTexture(explosionSprites[3]);
                          UnloadTexture(explosionSprites[4]);
                          UnloadTexture(frostExplosionSprites[0]);
                          UnloadTexture(frostExplosionSprites[1]);
                          UnloadTexture(frostExplosionSprites[2]);
                          UnloadTexture(frostExplosionSprites[3]);
                          UnloadTexture(frostExplosionSprites[4]);
                          UnloadTexture(groundTiles[0]);
                          UnloadTexture(groundTiles[1]);
                          UnloadTexture(groundTiles[2]);
                          UnloadTexture(groundTiles[3]);
                          UnloadTexture(groundTiles[4]);
                          UnloadTexture(groundTiles[5]);
                          UnloadTexture(groundTiles[6]);
                          UnloadTexture(groundTiles[7]);
                          UnloadTexture(groundTiles[8]);
                          UnloadTexture(groundTiles[9]);
                          UnloadTexture(fenceSprite);
                          UnloadTexture(bulletTimeSprite[0]);
                          UnloadTexture(bulletTimeSprite[1]);
                          UnloadTexture(fenceSprite_side);
                          UnloadTexture(fenceSprite_side_rotated);
                          UnloadImage(ikona);
                          StopSoundMulti();
                          UnloadSound(BCS);
                          UnloadSound(Wre);
                          UnloadSound(Eat);
                          UnloadSound(Bomb);
                          UnloadSound(frostBomb);
                          UnloadSound(bulletIn);
                          UnloadSound(bulletOut);
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
