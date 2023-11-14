/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:50:18 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/14 11:41:10 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_miniexit(t_data *data)
{
	if (data->args[1])
		ft_check_exit_args(data);
	if (data->lvl > 1)
	{
		ft_putstr_fd("exit", data->fdout);
		ft_display_banner_bye();
		data->lvl -= 1;
	}
	else
	{
		ft_putstr_fd("exit", data->fdout);
		ft_putchar_fd('\n', data->fdout);
		ft_free_all(data);
		ft_display_banner_bye();
		exit(EXIT_SUCCESS);
	}
}

void	ft_check_exit_args(t_data *data)
{
	if (ft_atoi(data->args[1]) != 0)
	{
		ft_putstr_fd(data->args[0], data->fdout);
		ft_putchar_fd('\n', data->fdout);
		ft_free_all(data);
		ft_display_banner_bye();
		exit(EXIT_FAILURE);
	}
	if (!ft_isdigit(data->args[1][0]))
	{
		ft_putstr_fd(data->args[0], data->fdout);
		ft_putchar_fd('\n', data->fdout);
		ft_putstr_fd("bash: ", data->fdout);
		ft_putstr_fd(data->args[0], data->fdout);
		ft_putstr_fd(": ", data->fdout);
		ft_putstr_fd(data->args[1], data->fdout);
		ft_putstr_fd(": numeric argument is required\n", data->fdout);
		ft_display_banner_bye();
		ft_free_all(data);
		exit(EXIT_FAILURE);
	}
}
