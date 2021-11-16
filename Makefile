# Makefile for ft_containers

NAME = cont
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
SOURCES = main_Map.cpp
HEADERS = Vector.hpp Utility.hpp Map.hpp Tree.hpp
OBJECTS = $(SOURCES:.cpp=.obj)

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.obj: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS)

fclean: clean
	-rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re