// Import bibliotek standardowych C/C++
#include "stdlib.h"
#include <ctime>
#include <vector>
// Import raylib
#include "libs/raylib.h"
#include "libs/raymath.h"
// Import naszych nagłówków
#include "monkey.h"
#include "snake.h"


int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 800;
  const int numberOfMonkeys = 25;
  std::vector<Malpa> monkeyList;
  Snake snake(10);

  srand(time(NULL));
  SetTargetFPS(60);
  InitWindow(screenWidth, screenHeight, "Snake");
  Vector2 windowPosition = {100, 100};
  SetWindowPosition(windowPosition.x, windowPosition.y);

  // wypelniamy liste malp Malpami
  for (int i = 0; i < numberOfMonkeys; i++)
  {
    monkeyList.push_back(Malpa());
  }

  // To jest główna pętla, wykonywana dopóki okno nie zostanie zamknięte
  while (!WindowShouldClose())
  {
    if (IsKeyDown(KEY_RIGHT))
      snake.velocity.x += .2;
    if (IsKeyDown(KEY_LEFT))
      snake.velocity.x += -.2;
    if (IsKeyDown(KEY_UP))
      snake.velocity.y += -.2;
    if (IsKeyDown(KEY_DOWN))
      snake.velocity.y += .2;

    // POCZĄTEK Rysowania
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < numberOfMonkeys; i++)
    {
      monkeyList[i].draw();
    }
    snake.update();
    snake.draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
