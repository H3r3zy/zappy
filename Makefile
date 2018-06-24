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

#default rule
all:		$(SERVER_NAME) zappy_ai

zappy_ai:
	@echo "AI built"

$(SERVER_NAME):	$(SERVER_OBJ)
	gcc -o $(SERVER_NAME) $(SERVER_OBJ) $(CFLAGS) $(SERVER_LDFLAGS)

.PHONY:		all

#clean all the .o
clean:
	rm -rf $(SERVER_OBJ)

.PHONY:		clean

#clean all the .o and the binary
fclean:		clean
	rm -rf $(SERVER_NAME)

.PHONY:		fclean

#recompile all the source
re:	fclean all

.PHONY:		re

#compile the program in debug mode
debug:		CFLAGS += -ggdb3 -DDEBUG=1

debug:		re

.PHONY:		debug
