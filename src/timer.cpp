#include "timer.h"

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
