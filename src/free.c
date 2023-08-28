/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:26:52 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/28 10:55:17 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_list(t_elist *lst)
{
	t_elist	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->name);
		//printf("%s\n", lst->name);
		free(lst->def);
		//printf("%s\n", lst->def);
		free(lst);
		lst = tmp;
	}
}

// void	ft_free_list(t_elist *lst)
// {
// 	while (lst)
// 	{
// 		free(lst->name);
// 		free(lst->def);
// 		free(lst);
// 		ft_free_list(lst->next);
// 	}
// }

void	ft_free_all(t_data *data)
{
	printf("ft_free_all-------------\n");
	clear_history();
	ft_free_double_pointer(data->args);
	free(data->input);
	ft_free_list(data->env);
	data->env = NULL;
	data = NULL;
}
