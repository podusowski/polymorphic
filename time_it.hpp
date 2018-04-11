#pragma once

#include <chrono>
#include <iostream>

using clock_type = std::chrono::high_resolution_clock;

struct time_it
{
    time_it()
        : _start(clock_type::now())
    {
    }

    ~time_it()
    {
        auto took = clock_type::now() - _start;
        std::cerr << "took " << took.count() << std::endl;
    }

private:
    clock_type::time_point _start;
};
