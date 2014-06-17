
#include "timer.h"
#include "stdafx.h"


double Timer::frequency = [] {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
    {
        throw "QueryPerformanceFrequency Failed!";
    }

    return double(li.QuadPart)/1000.0;
}();


void Timer::Reset()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    startedAt = li.QuadPart;
}


double Timer::GetTime()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - startedAt)/frequency;
}

