cmake_minimum_required(VERSION 3.10)
project(PSU_zappy_2017 C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SERVER_FILE
        src/*.c
        src
        src/server/debug.c
        )

file(GLOB SERVER_HEADER
        include/*.h
        include
        )

include_directories(include/server)
include_directories(include)

add_executable(server ${SERVER_FILE} ${SERVER_HEADER})
