#include "Benchmark.h"
#include <QDebug>



Benchmark::Benchmark()
{
    m_start_time = std::chrono::high_resolution_clock::now();
}

Benchmark::~Benchmark()
{
    auto end_time = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();
    auto duration = end - start;
    double ms = duration * 0.001;
    qDebug() << ms <<  "ms";
}

