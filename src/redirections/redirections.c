/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:57 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/28 19:36:17 by marirodr         ###   ########.fr       */
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
	t_token	*tmp;
	int		pfd[2];

	i = 0;
	tmp = data->token;
	while (i <= c_pipes)
	{
		if (pipe(pfd) == -1)
			perror("pipe");
		if (c_pipes == i)
		{
			printf("tengo que dirigir la ejecucion de los comandos a 1\n");
			//ft_exe_command(data, data->fdin, data->fdout); //si no hay pipe deja las salidas estandar predefinidas, que ya se hace asi de entrada en init
		}
		else
		{
			printf("tengo que redirigir las salidas entre procesos\n");
			//ft_exe_command(data, data->fdin, data->fdout); //aqui hay que cambiar ya las salidas con pipe
		}
		close(pfd[0]); //ceramos el fd del padre que no necesitamos , que es la parte "lectora" del pipe, porque eso "será" lo que reciba el proceso hijo de lo que escriba el padre con el fd[1] en el pipe
		i++;
	}
}
