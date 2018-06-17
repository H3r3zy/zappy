##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Graph Client Makefile
##

CC	=	g++

RM	=	rm -rf

SRC	=	src/main.cpp		\
		src/Entity/ARectangleShape.cpp	\
		src/Entity/AMotionShape.cpp	\
		src/Entity/Cell.cpp		\
		src/Entity/Character.cpp	\
		src/WindowInfo.cpp	\
		src/Grid.cpp		\
		src/Map.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	client

CXXFLAGS	=	-W -Wall -Wextra -IInclude -IInclude/Entity -g

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
