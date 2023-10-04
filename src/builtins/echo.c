/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/03 13:28:44 by marirodr         ###   ########.fr       */
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
	if (ft_is_flag(tmp->prev->str))
		tmp->prev->type = BUILTIN;
	while (data->args[pos] != NULL)
	{
		if (tmp->type >= NO_QUOTES && tmp->type <= D_QUOTES)
		{
			if (tmp->space == 1 && tmp->prev->type != BUILTIN)
				ft_putchar_fd(' ', data->fdout);
			ft_putstr_fd(data->args[pos], data->fdout);
		}
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
}
