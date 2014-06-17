
#pragma once

class Timer
{
public:
    Timer() { Reset(); }
    void Reset();
    double GetTime();
    static double frequency;
private:
    long long startedAt;
    
};

