/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:00:58 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/17 16:40:04 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
