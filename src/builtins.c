/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:43:04 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/24 15:21:56 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_builtin(t_data *data)
{
	if (ft_strcmp(data->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(data->args[0], "cd") == 0)
		return (2);
	if (ft_strcmp(data->args[0], "pwd") == 0)
		return (3);
	if (ft_strcmp(data->args[0], "export") == 0)
		return (4);
	if (ft_strcmp(data->args[0], "unset") == 0)
		return (5);
	if (ft_strcmp(data->args[0], "env") == 0)
		return (6);
	if (ft_strcmp(data->args[0], "exit") == 0)
		return (7);
	return (0);
}

void	ft_do_builtins(t_data *data)
{
	int	b;

	b = ft_is_builtin(data);
	if (b == 1)
		ft_echo(data);
	else if (b == 2)
		ft_cd(data);
	else if (b == 3)
		ft_pwd(data);
	else if (b == 4)
		ft_export(data);
	else if (b == 5)
		ft_unset(&data->env, data);
	else if (b == 6)
		ft_env(data, data->args);
	else if (b == 7)
		printf("HAZ CTRL-D VAGO");
}
