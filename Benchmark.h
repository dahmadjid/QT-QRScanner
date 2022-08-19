#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

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











#endif