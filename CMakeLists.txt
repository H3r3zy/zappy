cmake_minimum_required(VERSION 3.7.2)
project(client)

include_directories(
		Src
		Include/
		Include/Text/
		Include/Entity/
		Include/Tools/
		Include/Abstract/
		Include/Interface/
		Include/Class/
		Include/Class/Texture
		Include/Class/Gui/
		Include/Class/Gui/PersonalizedObject/
		Include/Class/Gui/Animation/
		Include/Class/Gui/ObjectSFML/
)

file(GLOB_RECURSE FILE Src/*.cpp Include/Interface/*.hpp Include/*.hpp)

set(CMAKE_CXX_STANDARD 11)
add_executable(client ${FILE})
target_compile_options(client PRIVATE -std=c++11 -W -Wall -Wextra -ggdb3)
target_link_libraries(client pthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)
