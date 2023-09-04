# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 16:22:32 by marirodr          #+#    #+#              #
#    Updated: 2023/09/04 17:00:25 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC 			= gcc -g #quitar -g

CFLAGS 		= -Wall -Wextra -Werror 

INC			= -I/Users/$(USER)/.brew/opt/readline/include 

RLINE		= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

LIBFT		= libft/libft.a

SRC			= src/main.c \
			  src/echo.c \
			  src/builtins.c \
			  src/list_utils.c \
			  src/list_utils_2.c \
			  src/list_utils_3.c \
			  src/echo_utils.c \
			  src/env_builtins.c \
			  src/cd.c \
			  src/free.c \
			  src/init.c \
			  src/signals.c \
			  src/fork.c \
			  src/quotes_utils.c \

OBJ			= $(SRC:.c=.o)

RM 			= rm -rf

GREEN		= \033[0;32m
RED			= \033[0;31m
END			= \033[0m

all:	$(NAME)

$(NAME): $(OBJ)
	@make -s -C libft
	$(CC) $(CFLAGS) $(LIBFT) $(RLINE) $(INC) $(OBJ) -o $(NAME) 
	@echo "$(GREEN)Minishell ready$(END)"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)Compiled objects have been removed$(END)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@echo "$(RED)Executables objects have been removed$(END)"

re: fclean all

.PHONY: all, clean, fclean, re
