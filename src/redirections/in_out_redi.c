/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:12:08 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/12 18:13:14 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_what_redi(t_data *data)
{
	t_token	*aux;

	aux = data->curr_tkn;
	if (aux->type == OUT)
	{
		ft_out_redi(data, 0);
	}
	else if (aux->type == APPEND)
	{
		ft_out_redi(data, 1);
	}
	else if (aux->type == IN)
	{
		ft_input_redi(data);
	}
	else if (aux->type == HERE_DOC)
	{
		ft_here_doc(data);
	}
	aux = aux->next;
}

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
		ft_putstr_fd("error opening file from ft_output_redi\n", data->fdout);
		return ;
	}
	data->fdout = new_fd;
	ft_free_double_pointer(split);
}

void	ft_input_redi(t_data *data)
{
	int		new_fd;
	char	**split;

	split = ft_split(data->curr_tkn->str, ' ');
	new_fd = open(split[1], O_RDONLY);
	if (new_fd == -1)
	{
		ft_putstr_fd("error opening file from ft_input_redi\n", data->fdout);
		return ;
	}
	data->fdin = new_fd;
	ft_free_double_pointer(split);
}

/*hay que crear un archivo (mejor oculto), redirigir la salida ahi, mantener
abierta la entrada por 0 hasta que encuentre EOF, cerrar y ejecutar
el comando sobre ese archivo. Luego eliminarlo con unlink(). */

void	ft_here_doc(t_data *data)
{
	int		here_doc;
	char	**split;
	char	*str;
	char	*dlm;

	split = ft_split(data->curr_tkn->str, ' ');
	str = NULL;
	here_doc = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dlm = ft_strjoin(split[1], "\n");
	if (here_doc == -1)
	{
		ft_putstr_fd("error opening file from ft_output_redi\n", data->fdout);
		return ;
	}
	data->fdout = here_doc;
	ft_putstr_fd("> ", 1);
	str = get_next_line(0);
	while (ft_strcmp(str, dlm) != 0)
	{
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(str, data->fdout);
		free(str);
		str = get_next_line(0);
	}
	close(here_doc);
	free(str);
	free(dlm);
	free(data->curr_tkn->str); 	//data->curr_tkn->str = NULL;
	data->curr_tkn->str = ft_strdup(".tmp");
	data->curr_tkn->type = NO_QUOTES;
	data->here_doc = 1;
	if (data->curr_tkn->prev != NULL)
	{
		data->curr_tkn = data->curr_tkn->prev;
		ft_free_double_pointer(data->args);
		ft_reconvert_token(data);
	}
	else
		data->here_doc = 2;
	ft_free_double_pointer(split);
}
