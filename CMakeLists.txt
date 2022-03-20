cmake_minimum_required(VERSION 3.21)
project(wicked_csv C)

set(CMAKE_C_STANDARD 23)

add_executable(wicked_csv src/main.c src/joiner.c src/joiner.h)
