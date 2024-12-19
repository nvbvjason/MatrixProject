#include "Timer.hpp"

#include <iostream>

Timer::Timer()
{
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end -start;
    const double ms = duration.count() * 1000.0;
    std::cout << "Timer took " << ms << " ms " << '\n';
}