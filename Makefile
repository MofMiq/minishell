# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 16:22:32 by marirodr          #+#    #+#              #
#    Updated: 2023/11/14 11:40:45 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC 			= gcc

CFLAGS 		= -Wall -Wextra -Werror 

INC			= -I/Users/$(USER)/.brew/opt/readline/include 

RLINE		= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

LIBFT		= libft/libft.a

SRC			= src/main.c \
			src/builtins/builtins.c \
			src/builtins/echo.c \
			src/builtins/cd.c \
			src/builtins/env_unset.c \
			src/builtins/exit.c \
			src/builtins/export.c \
			src/builtins/list_utils.c \
			src/builtins/list_utils_2.c \
			src/builtins/list_utils_3.c \
			src/exec/exec.c \
			src/exec/signals.c \
			src/parser/parser.c \
			src/parser/create_token.c \
			src/parser/dollar_parser.c \
			src/parser/quotes.c \
			src/parser/token_utils.c \
			src/parser/redi_parser.c \
			src/init.c \
			src/free.c \
			src/redirections/redirections.c \
			src/redirections/in_out_redi.c \

OBJ			= $(SRC:.c=.o)

RM 			= rm -rf

GREEN		= \033[0;32m
RED			= \033[0;31m
END			= \033[0m

all:	$(NAME)

$(NAME): $(OBJ)
	@make -s -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(RLINE) $(INC)
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
