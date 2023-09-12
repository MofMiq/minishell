/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/12 08:36:15 by begarijo         ###   ########.fr       */
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

/*Hacer función a parte, que compruebe que el argumento que se trata existe
 *
 * Seguramente haya que reestructurar todo, porque en el is flag doy por hecho que existe*/

void	ft_echo(t_data *data)
{
	int	flag;
	// int	i;

	// i = 0;
	flag = 0;
	// if (data->args[i] && ft_is_flag(data->args[1]))
	// {
	// 	flag = 1;
	// 	i++;
	// }
	// while (data->args[i] && ft_is_flag(data->args[i]))
	// 	i++;
	// while (data->args[i])
	// 	ft_print_echo(data, i);
	// if (flag == 0)
	// 	printf("\n");
	{
		if (data->argc == 2)
			printf("\n");
	}
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
