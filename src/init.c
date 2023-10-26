/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:10:56 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/26 16:28:33 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	*ft_init_data(char **env, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->env = ft_copy_env(env);
	ft_init_env(data->env);
	ft_graphic(data);
	ft_update_env(data);
	data->exp = NULL;
	data->input = NULL;
	data->args = argv;
	data->token = NULL;
	data->curr_tkn = NULL;
	data->argc = 0;
	data->child = 1;
	data->lvl = 1;
	data->fdin = STDIN_FILENO;
	data->fdout = STDOUT_FILENO;
	data->exit_status = 0;
	data->aux_space = -1;
	data->go = 0;
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
		if (ft_list_cmp(elist, "_") == 0)
			ft_update_list(elist, "./minishell", "_");
		elist = elist->next;
	}
	elist = tmp;
}

void	ft_update_env(t_data *data)
{
	t_elist	*node;
	char	*path_lvl;
	char	*aux;

	aux = getcwd(NULL, 0);
	path_lvl = ft_strjoin(aux, "/minishell");
	free(aux);
	ft_update_list(data->env, path_lvl, "SHELL");
	free(path_lvl);
	node = ft_search_node(data->env, "SHLVL");
	path_lvl = ft_itoa(ft_atoi(node->def) + 1);
	ft_update_list(data->env, path_lvl, "SHLVL");
	free(path_lvl);
}

void	ft_graphic(t_data *data)
{
	char	*matrix[2];
	t_elist	*aux;

	aux = ft_search_node(data->env, "USER");
	matrix[0] = "GRAPHIC";
	if (ft_strcmp(aux->def, "marirodr") == 0)
		matrix[1] = "/Users/marirodr/graphic";
	else
		matrix[1] = "RUTA_DE_BELEN";
	ft_add_back(&data->env, ft_new_node(matrix));
}
