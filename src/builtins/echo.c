/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/19 18:06:43 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print_echo(t_data *data, int pos)
{
	int		i;
	t_token	*tmp;

	i = pos - 1;
	tmp = data->token;
	if (tmp->next == NULL)
		return ;
	while (i >= 0)
	{
		tmp = tmp->next;
		i--;
	}
	while (data->args[pos] != NULL)
	{
		ft_putstr_fd(data->args[pos], data->fdout);
		if (data->args[pos + 1] != NULL)
			ft_putchar_fd(' ', data->fdout);
		pos++;
		tmp = tmp->next;
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
	data->exit_status = 0;
}
