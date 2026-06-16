include(FetchContent)

FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.18.3)
FetchContent_MakeAvailable(httplib)

add_executable(twopow-service main.cpp)
target_link_libraries(twopow-service PRIVATE twopow::twopow httplib::httplib)

install(TARGETS twopow-service RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
