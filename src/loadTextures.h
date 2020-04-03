#ifndef LOAD_TEXTURES_H
#define LOAD_TEXTURES_H


Texture2D fruitSprite = LoadTexture("assets/sprites/food/owocek.png");
Texture2D monkeySprite = LoadTexture("assets/sprites/enemies/monkey.png");
Texture2D snakeSprite = LoadTexture("assets/sprites/character/snake.png");
Texture2D nukeSprite = LoadTexture("assets/sprites/powerups/3.png");
Texture2D explosionSprites[5];
explosionSprites[0] = LoadTexture("assets/sprites/effects/explosion1.png");
explosionSprites[1] = LoadTexture("assets/sprites/effects/explosion2.png");
explosionSprites[2] = LoadTexture("assets/sprites/effects/explosion3.png");
explosionSprites[3] = LoadTexture("assets/sprites/effects/explosion4.png");
explosionSprites[4] = LoadTexture("assets/sprites/effects/explosion5.png");
Texture2D groundTile = LoadTexture("assets/sprites/tiles/Ground_Tile_01_B.png");
Texture2D fenceSprite = LoadTexture("assets/sprites/tiles/bush_pionowy.png");
Texture2D fenceSprite_side = LoadTexture("assets/sprites/tiles/bush_poziomy.png");
Texture2D fenceSprite_side_rotated = LoadTexture("assets//sprites/tiles/bush_poziomy_odbity.png");

#endif