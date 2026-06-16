# Fuzz targets require Clang's libFuzzer (-fsanitize=fuzzer).
add_executable(twopow_fuzz twopow_fuzz.cpp)
target_link_libraries(twopow_fuzz PRIVATE twopow::twopow)
target_compile_options(twopow_fuzz PRIVATE
    -g -O1 -fsanitize=fuzzer,address,undefined)
target_link_options(twopow_fuzz PRIVATE
    -fsanitize=fuzzer,address,undefined)

# Keep assertions live in the fuzzer regardless of build type.
target_compile_definitions(twopow_fuzz PRIVATE)
target_compile_options(twopow_fuzz PRIVATE -UNDEBUG)
