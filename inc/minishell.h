/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/08 17:04:51 by marirodr         ###   ########.fr       */
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
# include <sys/errno.h>
# include "../libft/libft.h"
// # include "../memory-leaks-master/include/memory_leaks.h"

# define BLUE "\033[0;96m"
# define END "\033[0m"

# define BUILTIN	1
# define NO_QUOTES	2
# define S_QUOTES	3
# define D_QUOTES	4

typedef struct s_token
{
	char			*str;
	int				type;
//	int				child;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

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
	//int		bool_exp; ya no sirve para su cometido original, reusable en futuro?
	int		argc;
	pid_t	child;
	t_elist	*env;
	t_elist	*exp;
	t_token	*token;
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
int		ft_check_name(char *name);
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

int		ft_is_builtin(char *str);
void	ft_do_builtins(t_data *data, char *str);

//main.c

void	ft_start_minishell(t_data *data);

//cd.c

void	ft_cd(t_data *data);
void	ft_change_dir(t_data *data, char *owd);
void	ft_pwd(void);
void	ft_oldpwd(t_data *data, char *owd, char *nwd);
void	ft_cmp_and_update(t_data *data, char *var_env, int i);

//free.c

void	ft_free_env(t_elist *lst);
void	ft_free_token(t_token *lst, t_data *data);
void	ft_free_all(t_data *data);

//init.c

t_data	*ft_init_data(char **env, char **argv);
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

//expand_env.c
void	ft_find_dollar(char **args, t_data *data);
int		ft_where_equal(char *str);
char	*ft_dollar_and_equal(char *str, t_elist *lst, char *arg);
char	*ft_equal_and_dollar(char *str, t_elist *lst, char *arg);

//parser.c
t_token	*ft_divide_input(t_data *data);
void	ft_init_parse(t_data *data);
t_token	*ft_assign_type(t_data *data);
void	ft_reconvert_token(t_data *data);

//token_utils.c
t_token	*ft_new_token(char *input, int i, int start);
t_token	*ft_last_token(t_token *token);
t_token	*ft_penultimate_token(t_token *token);
t_token	*ft_add_token(t_token **token, t_token *new);
t_token	*ft_parse_dollar(t_data *data);

//exec.c

void	ft_launch_exec(t_data *data);

#endif
