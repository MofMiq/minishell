/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/07 10:14:53 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_find_pos(t_data *data)
{
	int	flag;
	int	i;
	int	p;

	i = 1;
	p = i;
	flag = 0;
	while (ft_is_flag(data->args[1]))
	{
		flag = 1;
		if (ft_is_flag(data->args[i]) && ft_is_flag(data->args[i + 1]))
			p = i++;
		else if (ft_is_flag(data->args[i]) && !ft_is_flag(data->args[i + 1]))
		{
			p = i + 1;
			break ;
		}
	}
	ft_print_echo(data, p);
	return (flag);
}

void	ft_echo(t_data *data)
{
	int	flag;

	flag = 0;
	if (ft_check_argc(data) == 1)
	{
		flag = ft_find_pos(data);
		if (flag == 0)
			printf("\n");
	}
	else
	{
		flag = ft_check_argc(data);
		if (flag == 2)
			printf("\n");
	}
}
