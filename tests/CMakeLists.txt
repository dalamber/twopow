include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2)

# Prevent GoogleTest from overriding compiler/linker options on Windows.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(twopow_tests twopow_test.cpp)
target_link_libraries(twopow_tests PRIVATE twopow::twopow GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(twopow_tests)
