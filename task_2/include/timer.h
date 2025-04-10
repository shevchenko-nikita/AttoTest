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

        auto s = std::chrono::duration_cast<std::chrono::minutes>(end - start);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Execution time: " << s.count() << " minutes | " << ms.count() << " milliseconds" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> start;
};