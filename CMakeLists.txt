cmake_minimum_required(VERSION 3.20)
project(spsc_ring_buffer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)
if(ENABLE_TSAN)
    add_compile_options(-fsanitize=thread -g)
    add_link_options(-fsanitize=thread)
endif()

add_executable(spsc_ring_buffer
    src/main.cpp
    src/lamport_queue.cpp
)

target_include_directories(spsc_ring_buffer PRIVATE include)
