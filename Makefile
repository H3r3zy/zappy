##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile
##

##
## SERVER
##

CC		=	gcc

SERVER		=	server
SERVER_NAME	=	zappy_server

CFLAGS		=	-W -Wall -Wextra -Wno-unused-result

SERVER_DIR	=	src/server

SERVER_SRC	=	$(SERVER_DIR)/ai_protocol/broadcast.c		\
			$(SERVER_DIR)/ai_protocol/connect_nbr.c		\
			$(SERVER_DIR)/ai_protocol/die.c			\
			$(SERVER_DIR)/ai_protocol/eject.c		\
			$(SERVER_DIR)/ai_protocol/fork.c		\
			$(SERVER_DIR)/ai_protocol/incantation.c		\
			$(SERVER_DIR)/ai_protocol/inventory.c		\
			$(SERVER_DIR)/ai_protocol/look.c		\
			$(SERVER_DIR)/ai_protocol/movement.c		\
			$(SERVER_DIR)/ai_protocol/set.c			\
			$(SERVER_DIR)/ai_protocol/take.c		\
			$(SERVER_DIR)/client_manager/egg.c		\
			$(SERVER_DIR)/client_manager/end.c		\
			$(SERVER_DIR)/client_manager/join.c		\
			$(SERVER_DIR)/client_manager/leave.c		\
			$(SERVER_DIR)/client_manager/manager.c		\
			$(SERVER_DIR)/client_manager/msg_queue.c	\
			$(SERVER_DIR)/client_manager/read.c		\
			$(SERVER_DIR)/client_manager/orientation.c	\
			$(SERVER_DIR)/client_manager/teams.c		\
			$(SERVER_DIR)/debug.c				\
			$(SERVER_DIR)/graphic_protocol/action.c		\
			$(SERVER_DIR)/graphic_protocol/egg.c		\
			$(SERVER_DIR)/graphic_protocol/io.c		\
			$(SERVER_DIR)/graphic_protocol/map.c		\
			$(SERVER_DIR)/graphic_protocol/movement.c	\
			$(SERVER_DIR)/graphic_protocol/player.c		\
			$(SERVER_DIR)/graphic_protocol/quantification.c	\
			$(SERVER_DIR)/graphic_protocol/server.c		\
			$(SERVER_DIR)/graphic_protocol/status.c		\
			$(SERVER_DIR)/gui_manager/command.c		\
			$(SERVER_DIR)/gui_manager/manager.c		\
			$(SERVER_DIR)/loop.c				\
			$(SERVER_DIR)/main.c				\
			$(SERVER_DIR)/map.c				\
			$(SERVER_DIR)/parsing/game.c			\
			$(SERVER_DIR)/parsing/parser.c			\
			$(SERVER_DIR)/parsing/port.c			\
			$(SERVER_DIR)/parsing/string.c			\
			$(SERVER_DIR)/scheduler/add.c			\
			$(SERVER_DIR)/scheduler/resource.c		\
			$(SERVER_DIR)/scheduler/scheduler.c		\
			$(SERVER_DIR)/server.c				\
			$(SERVER_DIR)/socket/socket.c

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

SERVER_LDFLAGS	=	-lm

CFLAGS		+= 	-Iinclude/server

CFLAGS		+=	-O3

#
#			Graphical client
#

CXX		=	g++

CLIENT_SRC	=	Src/CstringArray.cpp							\
			Src/Grid.cpp								\
			Src/Main.cpp								\
			Src/ParseEnqueueMap.cpp							\
			Src/SfmlTool.cpp							\
			Src/WindowInfo.cpp							\
			Src/Tools/Thread.cpp							\
			Src/Text/AText.cpp							\
			Src/Text/GameText.cpp							\
			Src/Entity/AMotionShape.cpp						\
			Src/Entity/ARectangleShape.cpp						\
			Src/Entity/Cell.cpp							\
			Src/Entity/Character.cpp						\
			Src/Entity/Water.cpp							\
			Src/client/Auth.cpp							\
			Src/client/Communication.cpp						\
			Src/client/Gui.cpp							\
			Src/client/ManageDisplay.cpp						\
			Src/client/ManageServer.cpp						\
			Src/client/Map.cpp							\
			Src/client/Texture/GuiTexture.cpp					\
			Src/client/Texture/IATexture.cpp					\
			Src/client/Texture/shackTexture.cpp					\
			Src/client/Gui/SFML_monitor.cpp						\
			Src/client/Gui/Animation/Modal.cpp					\
			Src/client/Gui/PersonalizedObject/TextInputBckPlaceHorder.cpp		\
			Src/client/Gui/ObjectSFML/AbstractObjectSFML.cpp			\
			Src/client/Gui/ObjectSFML/Circle.cpp					\
			Src/client/Gui/ObjectSFML/Container.cpp					\
			Src/client/Gui/ObjectSFML/Sprite.cpp					\
			Src/client/Gui/ObjectSFML/Square.cpp					\
			Src/client/Gui/ObjectSFML/Text.cpp					\
			Src/client/Gui/ObjectSFML/TextInput.cpp					\

CLIENT_OBJ	=	$(CLIENT_SRC:.cpp=.o)

CPPFLAGS	=	-I Include/								\
			-I Include/Abstract/							\
			-I Include/Text/							\
			-I Include/Class/							\
			-I Include/Entity/							\
			-I Include/Interface/							\
			-I Include/Text/							\
			-I Include/Tools/							\
			-I Include/Class/Gui/							\
			-I Include/Class/Texture/						\
			-I Include/Class/Gui/Animation/						\
			-I Include/Class/Gui/ObjectSFML/					\
			-I Include/Class/Gui/PersonalizedObject/				\
			-W -Wall -Wextra

LDFLAGS_CLIENT	=	-pthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++11

CLIENT_NAME	=	zappy_client

#default rule
all:		$(SERVER_NAME) zappy_ai $(CLIENT_NAME)

zappy_ai:
	@echo "AI built"

$(SERVER_NAME):	$(SERVER_OBJ)
	gcc -o $(SERVER_NAME) $(SERVER_OBJ) $(CFLAGS) $(SERVER_LDFLAGS)

$(CLIENT_NAME):	$(CLIENT_OBJ)
	g++ -o $(CLIENT_NAME) $(CLIENT_OBJ) $(CPPFLAGS) $(LDFLAGS_CLIENT)

.PHONY:		all

#clean all the .o
clean:
	rm -rf $(SERVER_OBJ)
	rm -rf $(CLIENT_OBJ)

.PHONY:		clean

#clean all the .o and the binary
fclean:		clean
	rm -rf $(SERVER_NAME)
	rm -rf $(CLIENT_NAME)

.PHONY:		fclean

#recompile all the source
re:	fclean all

.PHONY:		re

#compile the program in debug mode
debug:		CFLAGS += -ggdb3 -DDEBUG=1

debug:		re

.PHONY:		debug
