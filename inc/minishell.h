/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/04 19:38:00 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../libft/libft.h"
// # include "../memory-leaks-master/include/memory_leaks.h"

# define BLUE "\033[0;96m"
# define END "\033[0m"

typedef struct s_elist
{
	char			*name;
	char			*def;
//	int				child;
	struct s_elist	*prev;
	struct s_elist	*next;
}	t_elist;

typedef struct s_data
{
	char	*input;
	char	**args;
	//int		bool_exp; ya no sirve para su cometido original, reusable en futuro?
	int		argc;
	t_elist	*env;
	t_elist	*exp;
}	t_data;

//list_utils.c

t_elist	*ft_new_node(char **splited);
t_elist	*ft_last_node(t_elist *node);
t_elist	*ft_penultimate_node(t_elist *lst);
t_elist	*ft_first_node(t_elist *node);
t_elist	*ft_add_back(t_elist **env, t_elist *new);

//list_utils2.c

int		ft_double_pointer_len(char **args);
t_elist	*ft_search_node(t_elist *elist, char *var_env);
int		ft_list_cmp(t_elist *elist, char *var_env);
void	ft_update_list(t_elist *elist, char *new_def, char *var_env);
void	ft_remove_if(t_elist *curr, char *str, t_elist **env);

//list_utils_3.c

void	ft_export_list(t_elist **exp_lst, char *var_name);
t_elist	*ft_copy_env(char **env);
void	ft_print_list(t_elist *env, t_elist *exp, int i);

//env_builtins.c

void	ft_env(t_data *data, char **args);
int	ft_check_name(char *name);
void	ft_export(t_data *data);
void	ft_unset(t_elist **env, t_elist **exp, t_data *data);
void	ft_miniexit(t_data *data);

//echo_utils.c

int		ft_is_space(char c);
void	epur_str(char *str);
void	ft_print_echo(t_data *data, int pos);
int		ft_is_flag(char *str);
int		ft_check_argc(t_data *data);

//echo.c

int		ft_find_pos(t_data *data);
void	ft_echo(t_data *data);

//builtins.c

int		ft_is_builtin(t_data *data);
void	ft_do_builtins(t_data *data);

//main.c

void	ft_start_minishell(t_data *data);

//cd.c

void	ft_cd(t_data *data);
void	ft_change_dir(t_data *data, char *owd);
void	ft_pwd(void);
void	ft_oldpwd(t_data *data, char *owd, char *nwd);
void	ft_cmp_and_update(t_data *data, char *var_env, int i);

//free.c

void	ft_free_list(t_elist *lst);
void	ft_free_all(t_data *data);

//init.c

t_data	*ft_init_data(char **env);
void	ft_init_env(t_elist *elist);

//signals.c

void	ft_init_sig(void);
void	ft_restart_input(int sig);
void	ft_ignore_sigquit(void);

//fork.c
//Unido con signals??

void	ft_childprocess(t_data *data);

//quotes_utils.c
int		ft_is_quote(char c);
int		ft_there_is_quote(char *str);
char	*ft_ignore_quotes(char *str);

#endif
