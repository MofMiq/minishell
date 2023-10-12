/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:10:56 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/12 17:26:29 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// data->child no creo que haga falta
// iniciar señales aqui???????

t_data	*ft_init_data(char **env, char **argv)
{
	t_data	*data;

	(void)env;
	data = (t_data *)malloc(sizeof(t_data));
	data->env = ft_copy_env(env);
	ft_init_env(data->env);
	data->exp = NULL;
	data->input = NULL;
	data->args = argv;
	data->token = NULL;
	data->curr_tkn = NULL;
	//data->bool_exp = 0;
	data->argc = 0;
	data->child = 0;
	data->fdin = STDIN_FILENO;
	data->fdout = STDOUT_FILENO;
	data->exit_status = -1;
	data->here_doc = 0;
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
		// if (ft_list_cmp(elist, "SHLVL") == 0)
			//ft_update_list(elist, elist->child, "SHLVL");
		elist = elist->next;
	}
	elist = tmp;
}
