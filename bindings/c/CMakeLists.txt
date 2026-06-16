enable_language(C)

add_library(twopow_c STATIC twopow_c.cpp)
add_library(twopow::c ALIAS twopow_c)

target_include_directories(twopow_c PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>")
target_link_libraries(twopow_c PUBLIC twopow::twopow)

install(TARGETS twopow_c
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if(TWOPOW_BUILD_TESTS)
    add_executable(twopow_c_test test/twopow_c_test.c)
    target_link_libraries(twopow_c_test PRIVATE twopow_c)
    add_test(NAME twopow_c_api COMMAND twopow_c_test)
endif()
