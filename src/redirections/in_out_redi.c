/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:12:08 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/02 16:20:09 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*This is like a handling function that calls the appropriate function based on
the type of redirection indicated by the token. Once this is done, we check if
there're more consecutive redirections and recursively call our function. We
don't continue this process if the following tokens are a pipe or some other
text.*/

void	ft_what_redi(t_data *data)
{
	t_token	*aux;

	aux = data->curr_tkn;
	if (aux->type == OUT)
		ft_out_redi(data, 0);
	else if (aux->type == APPEND)
		ft_out_redi(data, 1);
	else if (aux->type == IN)
		ft_input_redi(data);
	else if (aux->type == HERE_DOC)
		ft_here_doc(data);
	if (aux->next && (aux->next->type >= OUT && aux->next->type <= HERE_DOC))
	{
		aux = aux->next;
		data->curr_tkn = aux;
		ft_what_redi(data);
	}
	if (aux->next)
		aux = aux->next;
}

/*This function is used to implement the output redirections, '>' and '>>',
which redirect the output to a file descriptor, creating or opening the specified
file. The only diference between both of them is that 'simple' redirection (>)
overwrite the file in case that already exist -macro O_TRUNC in open() function-,
while 'double' redirection appends the text writen in the file to the already
existent text - macro O_CREAT in open() function-.*/

void	ft_out_redi(t_data *data, int flag)
{
	int		new_fd;
	char	**split;

	split = ft_split(data->curr_tkn->str, ' ');
	if (flag == 0)
		new_fd = open(split[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		new_fd = open(split[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (new_fd == -1)
	{
		ft_free_double_pointer(split);
		ft_putstr_fd("Error opening file\n", data->fdout);
		data->exit_status = 1;
		data->go = 1;
		return ;
	}
	data->fdout = new_fd;
	ft_free_double_pointer(split);
}

/*This function is used to implement the input redirection, '<', which redirect
the input to a file descriptor of an already existing file. In other words, the
input becomes the content of a file instead the keyboard.*/

void	ft_input_redi(t_data *data)
{
	int		new_fd;
	char	**split;

	split = ft_split(data->curr_tkn->str, ' ');
	new_fd = open(split[1], O_RDONLY);
	if (new_fd == -1)
	{
		ft_free_double_pointer(split);
		ft_putstr_fd("Error opening file\n", data->fdout);
		data->exit_status = 1;
		data->go = 1;
		return ;
	}
	data->fdin = new_fd;
	ft_free_double_pointer(split);
}

/* Here's the corrected English translation for both ft_here_doc() and
ft_open_and_write_hd():

We need to replicate the behavior of the Bash heredoc, and to do that, we create
a hidden file called '.tmp.' We obtain the 'delimiter' string, which serves as
the signal to stop writing. We collect input from the keyboard using
get_next_line() and write it to that hidden file. Then, we redirect the input to
that file descriptor to read the data from it. When we finish our shell, we
delete the file with unlink().*/

void	ft_here_doc(t_data *data)
{
	char	**split;
	char	*dlm;
	int		new_fd;

	split = ft_split(data->curr_tkn->str, ' ');
	if (split[1] == NULL)
	{
		ft_free_double_pointer(split);
		ft_putstr_fd("bash: syntax error near unexpected token\n", data->fdout);
		data->exit_status = 1;
		return ;
	}
	dlm = ft_strjoin(split[1], "\n");
	ft_open_and_write_hd(data, dlm);
	free(dlm);
	ft_free_double_pointer(split);
	new_fd = open(".tmp", O_RDONLY);
	data->fdin = new_fd;
}

void	ft_open_and_write_hd(t_data *data, char *dlm)
{
	int		h_d;
	char	*str;

	h_d = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (h_d == -1)
	{
		ft_putstr_fd("error opening file from ft_output_redi\n", data->fdout);
		data->exit_status = 1;
		data->go = 1;
		return ;
	}
	ft_putstr_fd("> ", 1);
	str = get_next_line(0);
	while (ft_strcmp(str, dlm) != 0)
	{
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(str, h_d);
		free(str);
		str = get_next_line(0);
	}
	close(h_d);
	free(str);
}
