# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 19:18:04 by jcohen            #+#    #+#              #
#    Updated: 2024/09/12 19:27:01 by jcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -pthread

# Directories
INCLUDES = includes
SRC = src
OBJ = obj

# Source files
SRCS = $(SRC)/main.c $(SRC)/init.c $(SRC)/utils.c

# Object files
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

# Executable name
NAME = philo

# Rules
all: $(NAME)

# Link object files into the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ):
	mkdir -p $(OBJ)

# Clean object files and the executable
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(OBJ)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
