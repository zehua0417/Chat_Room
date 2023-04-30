#include "timer.h"

Timer::Timer(int duration, int id)
{
    this->duration = duration;
    this->id = id;
}

bool Timer::OnTimer()
{
    static  int startTime = 0;
    int endTime = clock();
    if (endTime - startTime >= duration)
    {
        startTime = endTime;
        return true;
    }
    return false;
}
