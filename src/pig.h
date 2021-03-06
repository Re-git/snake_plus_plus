#ifndef __PIG_H_INCLUDED__
#define __PIG_H_INCLUDED__

#include "libs/raylib.h"
#include "libs/raymath.h"
#include <ctime>
#include "stdlib.h"
#include "timer.h"
#include <vector>



class Pig {
    public:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        float width, height;
        float maxspeed;      // Maximum speed
        float maxSeekForce;
        int dead;
        int frozen;
        Rectangle pigRec;
        Texture2D sprite;
        float iloscZjedzonych;
        Timer* freeze_timer;

        Pig(Texture2D pigSprite);
        void draw();
        void update();
        void limit(Vector2&, float);
        void applyForce(Vector2);
        void applyBehaviors(std::vector<Pig>&, Vector2);
        bool collide(Rectangle rec);
        Vector2 createPosition();
        Vector2 seek(Vector2);
};

#endif