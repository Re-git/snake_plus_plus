#ifndef UTILITY_H
#define UTILITY_H

enum GameState {mainMenuState, inGameState, deathScreenState, pauseState, quitState};
struct Area
{
    int left;
    int top;
    int right;
    int bottom;
};

#endif