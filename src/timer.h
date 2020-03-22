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

Timer::Timer(int time_limit)
{
    timeLimit = time_limit;
    timeCounter = 0;           
    prevTime = clock();
    currentTime = clock() - prevTime;
    timeCounter = currentTime*1000/CLOCKS_PER_SEC;
}

bool Timer::isReady()
{
    currentTime = clock() - prevTime;
    timeCounter = currentTime*1000/CLOCKS_PER_SEC;
    if (timeCounter >= timeLimit)
    {
        return true;
    }
    return false;
}

void Timer::reset()
{
    prevTime = clock();
    currentTime = clock() - prevTime;
    timeCounter = currentTime*1000/CLOCKS_PER_SEC;
}

void Timer::setLimit(int time_limit)
{
    timeLimit = time_limit;
}
unsigned int Timer::getLimit()
{
    return timeLimit;
}

unsigned long Timer::getTime()
{
    return timeCounter;
}

#endif