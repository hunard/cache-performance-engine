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
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_tests
    tests/test_cache.cpp
    src/cache.cpp
)

target_link_libraries(run_tests
    ${GTEST_LIBRARIES}
    pthread
)
