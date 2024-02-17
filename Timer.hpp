#pragma once

#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

struct Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration;
    Timer();
    ~Timer();
};

#endif //TIMER_HPP
