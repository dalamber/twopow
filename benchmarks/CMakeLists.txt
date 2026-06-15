include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.0)
FetchContent_MakeAvailable(benchmark)

add_executable(twopow_benchmark twopow_benchmark.cpp)
target_link_libraries(twopow_benchmark PRIVATE twopow::twopow benchmark::benchmark)
