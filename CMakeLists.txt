cmake_minimum_required(VERSION 3.10)
project(CachePerformanceEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(cache
    src/main.cpp
    src/cache.cpp
    src/trace_reader.cpp
    src/gpu_memory_model.cpp
)

add_executable(generate_traces
    traces/generate_traces.cpp
)
