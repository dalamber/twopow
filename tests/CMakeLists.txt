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

if(TWOPOW_BUILD_CLI)
    add_executable(twopow_cli_tests cli_test.cpp)
    target_link_libraries(twopow_cli_tests PRIVATE GTest::gtest_main)
    target_compile_definitions(twopow_cli_tests PRIVATE
        TWOPOW_CLI_PATH="$<TARGET_FILE:twopow-cli>")
    add_dependencies(twopow_cli_tests twopow-cli)
    gtest_discover_tests(twopow_cli_tests)
endif()
