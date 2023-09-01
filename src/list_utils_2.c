/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:25 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/01 15:14:16 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_double_pointer_len(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
		i++;
	return (i);
}

t_elist	*ft_search_node(t_elist *elist, char *var_env)
{
	t_elist	*tmp;

	tmp = elist;
	while (elist)
	{
		if (ft_strcmp(elist->name, var_env) == 0)
			return (elist);
		else
			elist = elist->next;
	}
	elist = tmp;
	return (tmp);
}

int	ft_list_cmp(t_elist *elist, char *var_env)
{
	t_elist	*tmp;

	tmp = elist;
	while (elist)
	{
		if (ft_strcmp(elist->name, var_env) == 0)
			return (0);
		else
			elist = elist->next;
	}
	elist = tmp;
	return (1);
}

void	ft_update_list(t_elist *elist, char *new_def, char *var_env)
{
	elist = ft_search_node(elist, var_env);
	if (elist != NULL)
	{
		free(elist->def);
		elist->def = ft_strdup(new_def);
	}
	elist = ft_first_node(elist);
}

void	ft_remove_if(t_elist *curr, char *str, t_elist **env)
{
	while (curr)
	{
		if (ft_strcmp(curr->name, str) == 0)
		{
			if (curr->prev == NULL)
			{
				*env = curr->next;
				if (*env)
					(*env)->prev = NULL;
			}
			else
			{
				curr->prev->next = curr->next;
				if (curr->next)
				{
					curr->next->prev = curr->prev;
				}
			}
			if (curr->def != NULL)
				free(curr->def);
			free(curr->name);
			free(curr);
		}
		curr = curr->next;
	}
}
