cmake_minimum_required(VERSION 3.7.2)
project(client)

set(CMAKE_CXX_STANDARD 11)

include_directories(
		Src
		Include/
		Include/Abstract
		Include/Interface
		Include/Class
		Include/Class/Gui
		Include/Class/Gui/Animation
		Include/Class/Gui/ObjectSFML
)

file(GLOB_RECURSE FILE Src/*.cpp Include/Interface/*.hpp Include/*.hpp)

add_executable(client
        ${FILE})

target_compile_options(client PRIVATE -W -Wall -Wextra -ggdb3 -w)

target_link_libraries(client pthread -lsfml-graphics -lsfml-window -lsfml-system)
