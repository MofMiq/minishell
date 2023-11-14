/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:26:52 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/14 11:40:50 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*In this file, we have memory deallocation functions, for both linked lists and
one in general.*/

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
}

void	ft_free_all(t_data *data)
{
	unlink(".tmp");
	clear_history();
	ft_free_env(data->env);
	data->env = NULL;
	if (data->token)
		ft_free_token(data->token, data);
}

/*This funtions is separated from ft_check_name() just because
42 norm of 25 lines. :(*/

int	ft_check_name_print(char *name, t_data *data)
{
	ft_putstr_fd("bash: export: ", data->fdout);
	ft_putstr_fd(name, data->fdout);
	ft_putstr_fd(": not a valid identifer\n", data->fdout);
	data->exit_status = 1;
	return (0);
}
