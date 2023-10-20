/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:43:04 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/20 16:47:18 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_builtin(char *str)
{
	if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "ECHO")))
		return (1);
	if (!(ft_strcmp(str, "cd")) || !(ft_strcmp(str, "CD")))
		return (2);
	if (!(ft_strcmp(str, "pwd")) || !(ft_strcmp(str, "PWD")))
		return (3);
	if (!(ft_strcmp(str, "export")) || !(ft_strcmp(str, "EXPORT")))
		return (4);
	if (!(ft_strcmp(str, "unset")) || !(ft_strcmp(str, "UNSET")))
		return (5);
	if (!(ft_strcmp(str, "env")) || !(ft_strcmp(str, "ENV")))
		return (6);
	if (!(ft_strcmp(str, "exit")) || !(ft_strcmp(str, "EXIT")))
		return (7);
	if (!(ft_strcmp(str, "./minishell")))
		return (8);
	return (0);
}

void	ft_do_builtins(t_data *data, char *str)
{
	int	b;

	b = ft_is_builtin(str);
	if (b == 1)
		ft_echo(data);
	else if (b == 2)
		ft_cd(data);
	else if (b == 3)
		ft_pwd(data);
	else if (b == 4)
	{
		data->exit_status = 0;
		if (data->argc == 1)
			ft_print_env(data, data->env, 2);
		ft_export(data);
	}
	else if (b == 5)
		ft_unset(&data->env, &data->exp, data);
	else if (b == 6)
		ft_env(data, data->args);
	else if (b == 7)
		ft_miniexit(data);
	else if (b == 8)
		data->lvl += 1;
}
