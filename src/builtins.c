/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:43:04 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/22 13:53:19 by begarijo         ###   ########.fr       */
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
	if (ft_strcmp(args[0], "env") == 0)
		return (5);
	if (ft_strcmp(args[0], "exit") == 0)
		return (6);
	return (0);
}

void	ft_do_builtins(char **args)
{
	int	b;

	b = ft_is_builtin(args);
	if (b == 1)
		ft_echo(args);
	else if (b == 2)
		printf("cd su primo \n");
	else if (b == 3)
		printf("pwd surmano\n");
	else if (b == 4)
		printf("exportame esta\n");
	else if (b == 5)
		printf("envidioso tu cochino");
	else if (b == 6)
		printf("HAZ CTRL-D VAGO");
}
