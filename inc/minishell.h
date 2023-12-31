/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/14 11:34:19 by marirodr         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"

# define BLUE "\033[0;96m"
# define PINK "\033[0;95m"
# define RED "\033[0;31m"
# define END "\033[0m"

# define BUILTIN	1
# define NO_QUOTES	2
# define S_QUOTES	3
# define D_QUOTES	4
# define PIPE		5
# define OUT		6
# define IN			7
# define APPEND		8
# define HERE_DOC	9

typedef struct s_token
{
	char			*str;
	int				type;
	int				space;
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
	int		argc;
	int		lvl;
	pid_t	child;
	int		fdin;
	int		fdout;
	int		exit_status;
	int		aux_space;
	int		go;
	t_elist	*env;
	t_elist	*exp;
	t_token	*token;
	t_token	*curr_tkn;
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
void	ft_print_env(t_data *data, t_elist *env, int i);
void	ft_print_exp(t_data *data, t_elist *exp);

//env_builtins.c

void	ft_env(t_data *data, char **args);
void	ft_unset(t_elist **env, t_elist **exp, t_data *data);
int		ft_env_size(t_elist *elist);

//export.c
int		ft_check_name(char *name, t_data *data);
void	ft_export(t_data *data);
char	**ft_no_char_in_split(char **matrix, char *str);
char	**ft_alt_split(char *str, char c);

//exit.c
void	ft_miniexit(t_data *data);
void	ft_check_exit_args(t_data *data);

//echo.c

void	ft_echo(t_data *data);
void	ft_print_echo(t_data *data, int pos);
int		ft_is_flag(char *str);

//builtins.c

int		ft_is_builtin(char *str);
void	ft_do_builtins(t_data *data, char *str);
int		ft_special_dir(t_data *data);

//main.c

void	ft_start_minishell(t_data *data);
void	ft_display_banner(void);
void	ft_display_banner_bye(void);

//cd.c

void	ft_cd(t_data *data, char *owd);
void	ft_change_dir(t_data *data, char *owd);
void	ft_pwd(t_data *data);
void	ft_oldpwd(t_data *data, char *owd, char *nwd);
void	ft_cmp_and_update(t_data *data, char *var_env, int i);

//free.c

void	ft_free_env(t_elist *lst);
void	ft_free_token(t_token *lst, t_data *data);
void	ft_free_all(t_data *data);
int		ft_check_name_print(char *name, t_data *data);

//init.c

t_data	*ft_init_data(char **env, char **argv);
void	ft_init_env(t_elist *elist);
void	ft_update_env(t_data *data);
void	ft_graphic(t_data *data);

//signals.c

void	ft_handler(int sig);
void	ft_signal(void);
void	ft_handler_process(int sig);
void	ft_signal_proc(void);

//parser.c
void	ft_init_parse(t_data *data);
t_token	*ft_divide_input(t_data *data);
void	ft_subdivide_input(t_data *data, int *i, int *start);
void	ft_assign_type(t_data *data);
void	ft_change_symbols(t_data *data);

//create_token.c
t_token	*ft_new_token(char *input, int i, int start, t_data *data);
t_token	*ft_last_token(t_token *token);
t_token	*ft_penultimate_token(t_token *token);
t_token	*ft_add_token(t_token **token, t_token *new);
int		ft_check_space(char c);

//dollar_parser.c
t_token	*ft_parse_dollar(t_data *data);
void	ft_dollar_aux(t_data *data, t_token **token, int *i);
char	*ft_exit_status(int exit_estatus, int *i);
void	ft_change_dollar(t_token **token, char *nstr, int drop, int take);
int		ft_is_all_space(char *input, t_data *data);

//quotes.c
int		ft_is_closed(char *str, char c);
int		ft_c_quotes(char *str, char q);
char	*ft_copy_no_quotes(char *token, char *copy, int i, int j);
void	ft_ignore_quotes(t_data *data);
void	ft_quotes(t_data *data, int *i, int *start, char q);

//token_utils.c
void	ft_join_glued_tokes(t_data *data);
void	ft_remove_if_token(t_token *curr, char *cstr, t_token **token, int i);
void	ft_reconvert_token(t_data *data);
int		ft_token_size(t_data *data);
int		ft_count_pipes(t_token *token);

//redi_parser.c
void	ft_sub_red(t_data *data, int *i, int *start, char c);
int		ft_bad_syntax(t_token *aux);
int		ft_bad_redi(t_token *token, int fd, t_data *data);
void	ft_add_space(t_data *data);

//redirections.c
void	ft_process_pipeline(t_data *data, int c_pipes);
void	ft_change_pipes_fds(t_data *data, int i, int c_pipes);
void	ft_begin_redi(t_data *data);
int		ft_advance_n_reconvert(t_data *data);
void	ft_close_fds(t_data *data, int limit);

//in_out_redi.c
void	ft_what_redi(t_data *data);
void	ft_out_redi(t_data *data, int flag);
void	ft_input_redi(t_data *data);
void	ft_here_doc(t_data *data);
void	ft_open_and_write_hd(t_data *data, char *dlm);

//exec.c

void	ft_launch_exec(t_data *data);
void	ft_running_exec(t_data *data);
void	ft_exec_from_path(t_data *data);
char	*ft_get_path(t_data *data);
char	**ft_reconvert_env(t_elist *elist);

#endif
