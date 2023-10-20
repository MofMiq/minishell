/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:14:05 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/20 17:06:25 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_data *data, char **args)
{
	if (data->argc == 1)
	{
		ft_print_env(data, data->env, 1);
		data->exit_status = 0;
	}
	else
	{
		ft_putstr_fd(args[0], data->fdout);
		ft_putstr_fd(": ", data->fdout);
		ft_putstr_fd(args[1], data->fdout);
		ft_putstr_fd(": ", data->fdout);
		if (chdir(data->args[1]) == 0)
		{
			data->exit_status = 126;
			ft_putstr_fd(strerror(EACCES), data->fdout);
		}
		else
		{
			data->exit_status = 1;
			ft_putstr_fd(strerror(ENOENT), data->fdout);
		}
		ft_putchar_fd('\n', data->fdout);
	}
}

void	ft_unset(t_elist **env, t_elist **exp, t_data *data)
{
	t_elist	*curr;
	t_elist	*curr2;
	int		i;

	if (data->argc > 1)
	{
		i = 1;
		while (data->args[i] != NULL)
		{
			curr = *env;
			curr2 = *exp;
			ft_remove_if(curr, data->args[i], env);
			ft_remove_if(curr2, data->args[i], exp);
			i++;
		}
	}
	data->exit_status = 0;
}

int	ft_env_size(t_elist *elist)
{
	t_elist	*aux;
	int		i;

	i = 0;
	aux = elist;
	while (elist)
	{
		elist = elist->next;
		i++;
	}
	elist = aux;
	return (i);
}
