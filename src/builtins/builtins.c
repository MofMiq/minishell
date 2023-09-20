/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:43:04 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/20 19:00:33 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_builtin(char *str)
{
	if ((ft_strcmp(str, "echo") == 0))
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (2);
	if (ft_strcmp(str, "pwd") == 0)
		return (3);
	if (ft_strcmp(str, "export") == 0)
		return (4);
	if (ft_strcmp(str, "unset") == 0)
		return (5);
	if (ft_strcmp(str, "env") == 0)
		return (6);
	if (ft_strcmp(str, "exit") == 0)
		return (7);
	if (ft_strcmp(str, "./minishell") == 0)
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
		ft_pwd();
	else if (b == 4)
		ft_export(data);
	else if (b == 5)
		ft_unset(&data->env, &data->exp, data);
	else if (b == 6)
		ft_env(data, data->args);
	else if (b == 7)
		ft_miniexit(data);
	// else if (b == 8)
	// 	ft_childprocess(data);
}
