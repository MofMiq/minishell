/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/22 16:33:30 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	epur_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (ft_is_space(str[i]))
			i++;
		while (!ft_is_space(str[i]) && str[i] != '\0')
		{
			write(1, &str[i], 1);
			i++;
		}
		while (ft_is_space(str[i]) && ft_is_space(str[i + 1]) && str[i + 1] != '\0')
			i++;
		if (ft_is_space(str[i]) && str[i + 1] != '\0')
			write(1, " ", 1);
	}
}

void	ft_print_echo(char **args, int pos)
{
	int	i;

	i = 0;
	while (args[pos + i] != NULL)
	{
		epur_str(args[pos + i]);
		if (args[pos + i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

void	ft_echo(char **args)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 1;
	j = 1;
	if (args[j][0] == '-' && args[j] != NULL)
	{
		while (args[j][i] == 'n' && args[j][i] != '\0')
		{
			i++;
			flag = 0;
			if (args[j][i] != '\0')
				flag = 1;
		}
		j++;
	}
	ft_print_echo(args, j);
	if (flag == 1)
		printf("\n");
}
