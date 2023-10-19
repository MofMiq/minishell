/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:12:08 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/19 19:06:41 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		data->exit_status = 1;
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
		data->exit_status = 1;
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
