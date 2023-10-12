/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:12:08 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/12 11:50:45 by marirodr         ###   ########.fr       */
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
	char	*write;

	split = ft_split(data->curr_tkn->str, ' ');
	write = NULL;
	here_doc = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (here_doc == -1)
	{
		ft_putstr_fd("error opening file from ft_output_redi\n", data->fdout);
		return ;
	}
	data->fdout = here_doc;
	// while (write != split[1])
	// {
	write = get_next_line(0);
	ft_putstr_fd(write, data->fdout);
	free(write);
	//}
	ft_putstr_fd("hola desde .tmp\n", data->fdout);
	ft_putstr_fd("HERE_DOC / data->fdin:", 1);
	ft_putnbr_fd(data->fdin, 1);
	ft_putchar_fd('\n', 1);
	close(here_doc);
	//free(write);
	//unlink(".tmp");
	return ;
}
