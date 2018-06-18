cmake_minimum_required(VERSION 3.7.2)
project(client)

include_directories(
		Src
		Include/
		Include/Tools/
		Include/Abstract
		Include/Interface
		Include/Class
		Include/Class/Gui
		Include/Class/Gui/PersonalizedObject
		Include/Class/Gui/Animation
		Include/Class/Gui/ObjectSFML
)

file(GLOB_RECURSE FILE Src/*.cpp Include/Interface/*.hpp Include/*.hpp)

set(CMAKE_CXX_STANDARD 11)
add_executable(client ${FILE})
target_compile_options(client PRIVATE -std=c++11 -W -Wall -Wextra -ggdb3 -w)
target_link_libraries(client pthread -lsfml-graphics -lsfml-window -lsfml-system)


set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG
        "-W -Wall -Wextra -g -Wno-unused-parameter -DDEBUG=1")
set(CMAKE_C_FLAGS_RELEASE
        "-W -Wall -Wextra -O3 -Wno-unused-parameter")

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

add_executable(zappy_server ${SERVER_FILE} ${SERVER_HEADER})

target_link_libraries(zappy_server m)
