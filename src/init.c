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

t_data	*ft_init_data(char **env)
{
	t_data	*data;

	(void)env;
	data = (t_data *)malloc(sizeof(t_data));
	data->env = ft_copy_env(env);
	ft_init_env(data->env);
	data->input = NULL;
	data->args = NULL;
	data->bool_exp = 0;
	data->argc = 0;
	return (data);
}

void	ft_init_env(t_elist *elist)
{
	t_elist	*tmp;

	tmp = elist;
	while (elist)
	{
		if (ft_list_cmp(elist, "ZSH") == 0)
			ft_remove_if(elist, "ZSH", &elist);
		if (ft_list_cmp(elist, "OLDPWD") == 0)
			ft_remove_if(elist, "OLDPWD", &elist);
		if (ft_list_cmp(elist, "SHELL") == 0)
			ft_update_list(elist, "minishell", "SHELL");
		if (ft_list_cmp(elist, "_") == 0)
			ft_update_list(elist, "./minishell", "_");
		elist = elist->next;
	}
	elist = tmp;
}
