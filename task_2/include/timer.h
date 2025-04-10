#pragma once

#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer() : start(std::chrono::steady_clock::now()) {}
    ~Timer()
    {
        auto end = std::chrono::steady_clock::now();

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto s = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        std::cout << "Execution time: " << s.count() << "seconds | " << ms.count() << "milliseconds" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> start;
};