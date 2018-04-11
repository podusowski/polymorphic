#pragma once

#include <chrono>
#include <iostream>

struct time_it
{
    using clock_type = std::chrono::high_resolution_clock;

    time_it()
        : _start(clock_type::now())
    {
    }

    ~time_it()
    {
        auto took = clock_type::now() - _start;
        std::cerr << "took " << took.count() << "ns" << std::endl;
    }

private:
    clock_type::time_point _start;
};
