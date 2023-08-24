/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/24 11:09:03 by marirodr         ###   ########.fr       */
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
	int		bool_exp;
	int		argc;
	t_elist	*env;
}	t_data;

//list_utils.c

t_elist	*ft_new_node(char **splited);
t_elist	*ft_last_node(t_elist *node);
t_elist	*ft_penultimate_node(t_elist *lst);
t_elist	*ft_first_node(t_elist *node);
t_elist	*ft_add_back(t_elist **env, t_elist *new);
t_elist	*ft_copy_env(char **env);

//utils.c

int		ft_double_pointer_len(char **args);
t_elist	*ft_list_cmp(t_data *data, char *var_env);

//echo.c

int		ft_is_space(char c);
void	epur_str(char *str);
void	ft_print_echo(t_data *data, int pos);
void	ft_echo(t_data *data);

//builtins.c

int		ft_is_builtin(t_data *data);
void	ft_do_builtins(t_data *data);

//main.c

t_data	*ft_init_data(char **env);
void	ft_start_minishell(t_data *data);

//cd.c

void	ft_cd(t_data *data);
void	ft_pwd(t_data *data);

// crear otro archivo pa builtins

//env_builtins.c

void	ft_env(t_data *data, char **args);
void	ft_export(t_data *data);
void	ft_unset(t_elist *env, t_data *data);

#endif
