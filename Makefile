# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moabid <moabid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/21 15:48:25 by moabid            #+#    #+#              #
#    Updated: 2023/01/21 18:14:52 by moabid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = ircserv

SOURCES 	= $(shell find . -name "*.cpp")
HEADERS 	= $(shell find . -name "*.hpp")

OBJECTS 	= $(patsubst %.cpp, %.o, $(SOURCES))
DEPENDS 	= $(patsubst %.cpp, %.d, $(SOURCES))

CFLAGS 		= -g -std=c++98

all: $(NAME)

%.o: %.cpp
	@$(CC) -Iincludes $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME): $(OBJECTS)
	@echo "Dependencies Compiled !"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "Compiled !"

clean:
	-@$(RM) $(OBJECTS) $(DEPENDS)
	-@$(RM) $(OBJECTS)
	@echo "Everything is Cleaned !"

fclean: clean
	-@$(RM) $(NAME)

re: clean all

.PHONY: re fclean clean all

-include $(DEPENDS)