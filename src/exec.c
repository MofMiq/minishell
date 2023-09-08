/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:47:53 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/08 14:11:38 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_launch_exec(t_data *data)
{
	int	stat;

	data->child = fork();
	if (data->child == 0)
	{
		ft_exec_from_path(data);
		if (execve(data->args[0], data->args, data->env) == -1)
			printf("Errorsito\n");
		ft_free_all(data);
	}
	else if (data->child < 0)
		perror(data->args[0]);
	else
	{
		waitpid(data->child, &stat, WUNTRACED);
	}
}
