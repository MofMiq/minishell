/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:57 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/02 13:46:28 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* This comment is for both ft_process_pipeline() and ft_change_pipes_fd()
functions because they were together in one before.

Here we will check whether there is a pipe/redirection in the input or not,
and decide which file descriptors (fds) we need to redirect both input and
output data to.

When the program starts (in 'ft_init'), everything is set to the default
values (0, 1, 2). Once we enter this part for the first time - every time we
have a new input - we reset the input to the default value (keyboard) just in
case we changed it from a previous input or closed it. Then we execute the pipe,
which will find two available fds to create a new reader and writer - not from
the perspective of the pipe, but from the processes; where one process should
write and another should read.
	1 - Whether there is no pipe or we have reached the last command of the
	pipeline, we reset our variable to the standard output (STDOUT_FILENO / 1)
	and close the reader part because we have already received the information
	from 'x,' thus avoiding conflicts with fds.
	2 - If there is a pipe, we reset the output to the new one we've created
	(fdout->fd[1]), where we 'store' the result of the previous command.

When we 'return' to this function after completing the entire process, we close
the new write fd (fd[1]) to prevent it from waiting for more data from another
source (from the keyboard). If that were to happen, we would need to send a
signal, and then it would work fine.

In case we don't return to this function, we redirect our variable to the new
read fd (fd[0]), so the process reads from there instead of from the
keyboard.*/

void	ft_process_pipeline(t_data *data, int c_pipes)
{
	int		i;

	i = 0;
	data->curr_tkn = data->token;
	while (i <= c_pipes && data->curr_tkn)
	{
		ft_change_pipes_fds(data, i, c_pipes);
		if (data->curr_tkn->next != NULL)
			data->curr_tkn = data->curr_tkn->next;
		data->token = data->curr_tkn;
		ft_free_double_pointer(data->args);
		data->go = 0;
		i++;
	}
	ft_close_fds(data, 3);
}

void	ft_change_pipes_fds(t_data *data, int i, int c_pipes)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		data->exit_status = 1;
	}
	if (c_pipes == i)
	{
		data->fdout = STDOUT_FILENO;
		ft_begin_redi(data);
		close(fd[0]);
	}
	else
	{
		data->fdout = fd[1];
		ft_begin_redi(data);
	}
	close(fd[1]);
	data->fdin = fd[0];
}
/*In this function, we're basically going to search for whether there is a
redirection in the input, regardless of whether there is a pipe or not. We'll
call ft_advance_n_reconvert() function to convert some tokens to 'char **.'
If there is a redirection, we'll proceed to a function that will redirect the
input or output based on which one it is and then execute its action. Otherwise,
we'll check if the tokens are built-in or not to go to different places
accordingly.*/

void	ft_begin_redi(t_data *data)
{
	int	flag;

	flag = ft_advance_n_reconvert(data);
	if (flag == 1)
		ft_what_redi(data);
	if (data->args[0] == NULL || data->go == 1)
		return ;
	if (data->token->type == BUILTIN)
		ft_do_builtins(data, data->token->str);
	else
		ft_launch_exec(data);
}

/*This fucntion is used to convert all the tokens until a new redirection
is found, and in that case, we'll stop there to convert only the previous
tokens into 'char **.*/

int	ft_advance_n_reconvert(t_data *data)
{
	int	flag;

	flag = 0;
	if (data->curr_tkn->type == PIPE)
	{
		data->curr_tkn = data->curr_tkn->next;
		data->token = data->curr_tkn;
	}
	ft_reconvert_token(data);
	while (data->curr_tkn && data->curr_tkn->type != PIPE)
	{
		if (data->curr_tkn->type >= OUT && data->curr_tkn->type <= HERE_DOC)
		{
			flag = 1;
			break ;
		}
		if (data->curr_tkn->next == NULL)
			break ;
		data->curr_tkn = data->curr_tkn->next;
	}
	return (flag);
}

/*This function closes all file descriptors (fd) when it is called at the end
of 'ft_process_pipeline,' which means once we have finished reading the entire
input. Additionally, the values of 'data->fdin' and 'data->fdout' are reset to
their original values, 0 and 1, respectively.*/

void	ft_close_fds(t_data *data, int limit)
{
	if (data->fdin == STDIN_FILENO && data->fdout == STDOUT_FILENO)
		return ;
	while (data->fdin >= limit)
	{
		close(data->fdin);
		data->fdin--;
	}
	data->fdin = STDIN_FILENO;
	while (data->fdout >= limit)
	{
		close(data->fdout);
		data->fdout--;
	}
	data->fdout = STDOUT_FILENO;
}
