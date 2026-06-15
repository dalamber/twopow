add_executable(twopow-cli main.cpp)
target_link_libraries(twopow-cli PRIVATE twopow::twopow)
target_compile_definitions(twopow-cli PRIVATE
    TWOPOW_VERSION="${PROJECT_VERSION}")

install(TARGETS twopow-cli RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES "${CMAKE_SOURCE_DIR}/man/twopow-cli.1"
    DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
