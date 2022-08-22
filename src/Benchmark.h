#pragma once 



#include <iostream>
#include <chrono>



class Benchmark
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
public:
    Benchmark();
    ~Benchmark();
};


