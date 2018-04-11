#pragma once

#include <chrono>

struct time_it
{
    time_it()
        : _start(std::chrono::high_resolution_clock::now())
    {
    }

private:
    std::chrono::high_resolution_clock::time_point _start;
};
