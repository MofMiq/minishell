/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:26:52 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/09 14:41:39 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_env(t_elist *lst)
{
	t_elist	*tmp;

	while (lst)
	{
		tmp = lst->next;
		lst->prev = NULL;
		free(lst->def);
		free(lst->name);
		free(lst);
		lst = tmp;
	}
}

void	ft_free_token(t_token *lst, t_data *data)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		lst->prev = NULL;
		free(lst->str);
		free(lst);
		lst = tmp;
	}
	data->token = NULL;
	//esta movie la tenemos que mirar bien y ver donde y como peta
	//free(data->input);
	// if (data->args)
	// 	ft_free_double_pointer(data->args);
}

void	ft_free_all(t_data *data)
{
	ft_putstr_fd("ft_free_all-------------\n", data->fdout);
	clear_history();
	ft_free_env(data->env);
	data->env = NULL;
	if (data->token)
		ft_free_token(data->token, data);
}

int	ft_check_name_print(char *name, t_data *data)
{
	//perror("export");
	ft_putstr_fd("bash: export: ", data->fdout);
	ft_putstr_fd(name, data->fdout);
	ft_putstr_fd(": not a valid identifer\n", data->fdout);
	return (0);
}
