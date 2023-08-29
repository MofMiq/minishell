/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:10:56 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/29 15:40:52 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init_env(t_data *data)
{
	t_elist	*tmp;

	tmp = data->env;
	while (data->env)
	{
		if (ft_list_cmp(data, "OLDPWD") == 0)
			ft_remove_if(data->env, "OLDPWD", &data->env);
		if (ft_list_cmp(data, "ZSH") == 0)
			ft_remove_if(data->env, "ZSH", &data->env);
		data->env = data->env->next;
	}
	data->env = tmp;
}
