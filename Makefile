# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 16:22:32 by marirodr          #+#    #+#              #
#    Updated: 2023/08/22 13:55:27 by begarijo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC 			= gcc

CFLAGS 	= -Wall -Wextra -Werror

RLINE		= -I/Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

LIBFT		= libft/libft.a

SRC			= src/main.c \
			  src/echo.c \
			  src/builtins.c \

OBJ			= $(SRC:.c=.o)

RM 			= rm -rf

GREEN		= \033[0;32m
RED			= \033[0;31m
END			= \033[0m

all:	$(NAME)

$(NAME): $(OBJ)
	@make -s -C libft
	$(CC) $(CFLAGS) $(LIBFT) $(RLINE) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Minishell ready$(END)"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)Compiled objects have been removed$(END)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@echo "$(RED)Executables objects have been removed$(END)"

re: fclean all

.PHONY: all, clean, fclean, re
