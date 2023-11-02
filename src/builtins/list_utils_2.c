/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:25 by begarijo          #+#    #+#             */
/*   Updated: 2023/11/02 17:33:05 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*This function returns the size of a matrix.*/

int	ft_double_pointer_len(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
		i++;
	return (i);
}

/*This fucntion is used to search and return a node of a t_elist variable by the
name of environmental variable.*/

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

/*This function return 0 if it can find a certain node in a t_elist variable;
1 if not.*/

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

/*This function modifies the value of a environmental variable with a new
value.*/

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

/*This function deletes a node from a t_elist varible if it matches with str.*/

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
