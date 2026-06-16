cmake_minimum_required(VERSION 3.20)

project(twopow
    VERSION 0.1.0
    DESCRIPTION "Deterministic base-2 exponentiation for modern C++"
    HOMEPAGE_URL "https://github.com/dalamber/twopow"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

option(TWOPOW_BUILD_CLI "Build the twopow-cli application" ON)
option(TWOPOW_BUILD_TESTS "Build the test suite" ON)
option(TWOPOW_BUILD_BENCHMARKS "Build the benchmark suite" OFF)
option(TWOPOW_BUILD_C_API "Build the C API binding" OFF)
option(TWOPOW_BUILD_PYTHON "Build the Python binding" OFF)
option(TWOPOW_BUILD_SERVICE "Build the HTTP service" OFF)
option(TWOPOW_ENABLE_COVERAGE "Enable coverage instrumentation" OFF)

# --- Library target -------------------------------------------------------
add_library(twopow src/twopow.cpp)
add_library(twopow::twopow ALIAS twopow)

target_include_directories(twopow PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>")

target_compile_features(twopow PUBLIC cxx_std_20)

if(TWOPOW_ENABLE_COVERAGE)
    target_compile_options(twopow PUBLIC --coverage -O0 -g)
    target_link_options(twopow PUBLIC --coverage)
endif()

# --- Install layout (must precede subdirectories that install) ------------
include(GNUInstallDirs)

# --- Subdirectories -------------------------------------------------------
if(TWOPOW_BUILD_CLI)
    add_subdirectory(app)
endif()

if(TWOPOW_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(TWOPOW_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(TWOPOW_BUILD_C_API)
    add_subdirectory(bindings/c)
endif()

if(TWOPOW_BUILD_PYTHON)
    add_subdirectory(bindings/python)
endif()

if(TWOPOW_BUILD_SERVICE)
    add_subdirectory(service)
endif()

# --- Install / export -----------------------------------------------------
include(CMakePackageConfigHelpers)

install(TARGETS twopow
    EXPORT twopowTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT twopowTargets
    FILE twopowTargets.cmake
    NAMESPACE twopow::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/twopow)

configure_package_config_file(
    cmake/twopowConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/twopowConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/twopow)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/twopowConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/twopowConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/twopowConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/twopow)

# --- Packaging ------------------------------------------------------------
set(CPACK_PACKAGE_NAME "twopow")
set(CPACK_PACKAGE_VENDOR "Anton Shpakovskiy")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include(CPack)
