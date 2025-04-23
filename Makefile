# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egerin <egerin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 15:20:58 by egerin            #+#    #+#              #
#    Updated: 2025/04/23 15:51:20 by egerin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft
LIBFT_TARGET = ${LIBFT}/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I${LIBFT}  -Iincludes -g
LDFLAGS = -L${LIBFT} -lft
SRC_FILES = src/main.c
SRC = $(SRC_FILES)
OBJ = $(SRC:.c=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_TARGET)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "✅ $(_GREEN)Compiled succesfully ! ✅"

all: $(NAME)

$(LIBFT_TARGET):
	@make --no-print-directory -C $(LIBFT)

clean:
	@make --no-print-directory clean -C ${LIBFT}
	@rm -f $(OBJ)
	@echo "🚮 $(_RED)Deleted succesfully ! 🚮"

fclean: clean
	@make --no-print-directory fclean -C ${LIBFT}
	@rm -f $(NAME)

re:fclean all

.PHONY: all clean fclean re

_GREY=$'\x1b[30m'
_RED=\e[1;31m
_GREEN=\e[1;32m
_YELLOW=$'\x1b[33m'
_BLUE=$'\x1b[34m'
_PURPLE=$'\x1b[35m'
_CYAN=$'\x1b[36m'
_WHITE=$'\x1b[37m'
