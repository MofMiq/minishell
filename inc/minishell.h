/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/22 18:28:26 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_elist
{
	char			*name;
	char			*def;
	struct s_elist	*prev;
	struct s_elist	*next;
}	t_elist;

typedef struct s_data
{
	char	*input;
	char	**args;
	t_elist	*env;
}	t_data;

//list_utils.c

t_elist	*ft_new_node(char **splited);
t_elist	*ft_last_node(t_elist *node);
t_elist	*ft_add_back(t_elist **env, t_elist *new);
t_elist	*ft_copy_env(char **env);
void	ft_env(t_elist *env, char **args);

//echo.c

int		ft_is_space(char c);
void	epur_str(char *str);
void	ft_print_echo(char **args, int pos);
void	ft_echo(char **args);

//builtins.c

int		ft_is_builtin(char **args);
void	ft_do_builtins(char **args, t_data *data);

//main.c

t_data	*ft_init_data(char **env);

// crear otro archivo pa builtins

#endif
