/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:00:58 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/21 18:19:01 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Esto en principio esta como el culo, en exec.c hace practicamente lo mismo
// data->child creo que ya no me hace falta

void	ft_childprocess(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	//Belen! segun manu aqui sobra ft_start_minishel porque lo que hay que haer en realidad es un execve poniendole path absoluto
		ft_start_minishell(data);
	else if (pid > 0)
	{
		//data->child += 1;
		//ft_start_minishell(data);
		waitpid(pid, &status, WUNTRACED);
	}
	else
		printf("Childprocess failed\n");
}
