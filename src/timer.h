#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer
{
private:
    unsigned long timeCounter; // Time counted in ms
    unsigned int timeLimit;  
    clock_t prevTime;
    clock_t currentTime;
public:
    Timer(int);
    bool isReady();
    void reset();
    void setLimit(int);
    unsigned int getLimit();
    unsigned long getTime();
};

#endif
