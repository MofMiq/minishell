/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:43:04 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/23 12:16:57 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (2);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (3);
	if (ft_strcmp(args[0], "export") == 0)
		return (4);
	if (ft_strcmp(args[0], "unset") == 0)
		return (5);
	if (ft_strcmp(args[0], "env") == 0)
		return (6);
	if (ft_strcmp(args[0], "exit") == 0)
		return (7);
	return (0);
}

void	ft_do_builtins(char **args, t_data *data)
{
	int	b;

	b = ft_is_builtin(args);
	if (b == 1)
		ft_echo(args);
	else if (b == 2)
		ft_cd(data);
	else if (b == 3)
		ft_pwd(data);
	else if (b == 4)
		printf("exportame esta\n");
	else if (b == 5)
		printf("envidioso tu cochino");
	else if (b == 6)
	{
		if (data->argc > 1)
			printf("FATALISIMO");
		else
			ft_env(data->env, args);
	}
	else if (b == 7)
		printf("HAZ CTRL-D VAGO");
}
