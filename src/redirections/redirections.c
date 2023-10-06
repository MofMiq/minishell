/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:57 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/06 19:08:46 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_count_pipes(t_token *token)
{
	int		c;
	t_token	*tmp;

	c = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			c++;
		tmp = tmp->next;
	}
	return (c);
}

void	ft_process_pipeline(t_data *data, int c_pipes)
{
	int		i;
	int		fd[2];

	i = 0;
	data->curr_tkn = data->token;
	data->fdin = STDIN_FILENO; //podra hacer esto desde otro sitio?
	while (i <= c_pipes && data->curr_tkn)
	{
		if (pipe(fd) == -1)
			perror("pipe");
		if (c_pipes == i)
			ft_begin_redi(data);
		else
		{
			data->fdout = fd[1];
			ft_begin_redi(data);
		}
		close(fd[1]); //ceramos el fd del padre que no necesitamos , que es la parte "lectora" del pipe, porque eso "será" lo que reciba el proceso hijo de lo que escriba el padre con el fd[1] en el pipe
		data->fdin = fd[0];
		if (data->curr_tkn)
			data->curr_tkn = data->curr_tkn->next;
		ft_free_double_pointer(data->args);
		i++;
	}
}

	// int i = 0;
	// while (data->args[i])
	// {
	// 	printf("%sen ft_begin_redi: data->args[%i]: %s%s\n", BLUE, i, data->args[i], END);
	// 	i++;
	// }

void	ft_begin_redi(t_data *data)
{
	int	flag;

	flag = 0;
	ft_reconvert_token(data);
	while (data->curr_tkn && data->curr_tkn->type != PIPE)
	{
		if (data->curr_tkn->type >= OUT && data->curr_tkn->type <= HERE_DOC)
		{
			flag = 1;
			break ;
		}
		data->curr_tkn = data->curr_tkn->next;
	}
	if (flag == 1)
	{
		ft_what_redi(data);
	}
	else
	{
		ft_is_buil_or_comm(data);
	}
}

		// printf("ft_begin_redi: me voy a ft_what_redi\n");
		// printf("ft_begin_redi: me voy a me voy a ft_is_buil_or_comm\n");
		// printf("ft_is_buil_or_comm: nos vamos a ft_do_builtin\n");
		// printf("ft_is_buil_or_comm: nos vamos a ft_launch_process\n");

void	ft_is_buil_or_comm(t_data *data)
{
	if (data->token->type == BUILTIN)
	{
		ft_do_builtins(data, data->token->str);
	}
	else
	{
		ft_launch_exec(data);
	}
}

void	ft_what_redi(t_data *data)
{
	t_token	*aux;

	aux = data->curr_tkn;
	if (aux->type == OUT)
		ft_out_redi(data, 0);
	else if (aux->type == APPEDEN)
		ft_out_redi(data, 1);
	else if (aux->type == IN)
		ft_input_redi(data);
	else if (aux->type == HERE_DOC)
		ft_here_doc(data);
	aux = aux->next;
	ft_is_buil_or_comm(data);
}

void	ft_out_redi(t_data *data, int flag)
{
	int		new_fd;
	char	**matrix;

	matrix = ft_split(data->curr_tkn->str, ' ');
	if (flag == 0)
		new_fd = open(matrix[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		new_fd = open(matrix[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	data->fdout = new_fd;
	// if (data->fdout != STDOUT_FILENO) //esto es para cuando haya mas de una redireccion
	// 	close(data->fdout);
	ft_free_double_pointer(matrix);
}

void	ft_input_redi(t_data *data)
{
	int		new_fd;
	char	**matrix;

	matrix = ft_split(data->curr_tkn->str, ' ');
	new_fd = open(matrix[1], O_RDONLY);
	if (new_fd == -1)
	{
		ft_putstr_fd("error opening file from fT_input_redi\n", data->fdout);
		return ;
	}
	// if (data->fdin != STDIN_FILENO) //esto es para cuando haya mas de una redireccion
	// 	close(data->fdin);
	data->fdin = new_fd;
	ft_free_double_pointer(matrix);
}

void	ft_here_doc(t_data *data)
{
	ft_putstr_fd("ni puta idea todavia de que va esto exactamente\n", data->fdout);
	return ;
}
