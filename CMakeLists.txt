cmake_minimum_required(VERSION 3.9)
project(PSU_zappy_2017)

set(CMAKE_CXX_STANDARD 11)

include_directories(Include Include/Entity)

add_executable(PSU_zappy_2017
        src/main.cpp src/Map.cpp Include/Map.hpp src/Entity/Cell.cpp Include/Entity/Cell.hpp src/Grid.cpp Include/Grid.hpp src/WindowInfo.cpp Include/WindowInfo.hpp src/Entity/Character.cpp Include/Entity/Character.hpp Include/Entity/IEntity.hpp src/Entity/ARectangleShape.cpp Include/Entity/ARectangleShape.hpp src/Entity/AMotionShape.cpp Include/Entity/AMotionShape.hpp src/Text/AText.cpp Include/Text/AText.hpp src/Text/GameText.cpp Include/Text/GameText.hpp)
