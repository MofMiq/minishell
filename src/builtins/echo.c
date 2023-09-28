/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/26 18:19:01 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	epur_str(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (ft_is_space(str[i]))
			i++;
		while (!ft_is_space(str[i]) && str[i] != '\0')
		{
			ft_putchar_fd(str[i], data->fdout);
			//write(1, &str[i], 1);
			i++;
		}
		while (ft_is_space(str[i]) && (ft_is_space(str[i + 1])
				|| str[i + 1] != '\0'))
			i++;
		if (ft_is_space(str[i]) && str[i + 1] != '\0')
			ft_putchar_fd(' ', data->fdout);
			//write(1, " ", 1);
	}
}

void	ft_print_echo(t_data *data, int pos)
{
	while (data->args[pos] != NULL)
	{
		epur_str(data->args[pos], data);
		if (data->args[pos + 1] != NULL)
			ft_putchar_fd(' ', data->fdout);
			//write(1, " ", 1);
		pos++;
	}
}

int	ft_is_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\0' && str[0] == '-')
	{
		while (str[i] == 'n' && str[i] != '\0')
		{
			i++;
			if (str[i - 1] == 'n' && str[i] == '\0')
				return (1);
		}
		return (0);
	}
	return (0);
}

void	ft_echo(t_data *data)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (data->args[i] && ft_is_flag(data->args[i]))
	{
		flag = 1;
		i++;
	}
	while (data->args[i] && ft_is_flag(data->args[i]))
		i++;
	ft_print_echo(data, i);
	if (flag == 0)
		ft_putchar_fd('\n', data->fdout);
		//printf("\n");
}
