cmake_minimum_required(VERSION 3.20)
project(twopow_jni LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(JNI REQUIRED)

add_library(twopow_jni SHARED
    twopow_jni.c
    vendor/twopow.cpp
    vendor/twopow_c.cpp)

target_include_directories(twopow_jni PRIVATE vendor ${JNI_INCLUDE_DIRS})
set_target_properties(twopow_jni PROPERTIES POSITION_INDEPENDENT_CODE ON)
