/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:13:55 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/11 18:40:41 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		while (ft_is_space(str[i]) && (ft_is_space(str[i + 1])
				|| str[i + 1] != '\0'))
			i++;
		if (ft_is_space(str[i]) && str[i + 1] != '\0')
			write(1, " ", 1);
	}
}

void	ft_print_echo(t_data *data, int pos)
{
	while (data->args[pos] != NULL)
	{
		epur_str(data->args[pos]);
		if (data->args[pos + 1] != NULL)
			write(1, " ", 1);
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

int	ft_check_argc(t_data *data)
{
	int	i;

	i = 1;
	if (data->argc <= 2)
	{
		if (data->argc == 1)
			i = 2;
		else if (data->argc == 2 && !data->args[1])
			return (4);
		else if (data->argc == 2 && ft_is_flag(data->args[1]))
			i = 3;
	}
	else if (data->argc > 2)
	{
		if (data->argc == 3 && ft_is_flag(data->args[1]))
			return (4);
	}
	return (i);
}
