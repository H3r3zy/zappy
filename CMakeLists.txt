cmake_minimum_required(VERSION 3.10)
project(PSU_zappy_2017 C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SERVER_FILE
        src
        src/*.c
        src/server/debug.c
        )

file(GLOB SERVER_HEADER
        include/*.h
        include
        )

include_directories(include/server)
include_directories(include)

add_definitions(-DDEBUG=1)

add_executable(zappy_server ${SERVER_FILE} ${SERVER_HEADER})
