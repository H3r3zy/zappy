cmake_minimum_required(VERSION 3.9)
project(PSU_zappy_2017)

set(CMAKE_CXX_STANDARD 11)

add_executable(PSU_zappy_2017
        src/main.cpp src/Map.cpp src/Map.hpp src/Cell.cpp src/Cell.hpp src/Grid.cpp src/Grid.hpp src/WindowInfo.cpp src/WindowInfo.hpp src/Character.cpp src/Character.hpp)
