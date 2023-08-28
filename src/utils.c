/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:25 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/28 10:28:34 by begarijo         ###   ########.fr       */
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

t_elist	*ft_search_node(t_data *data, char *var_env)
{
	t_elist	*tmp;

	tmp = data->env;
	while (data->env)
	{
		if (ft_strcmp(data->env->name, var_env) == 0)
			return (data->env);
		else
			data->env = data->env->next;
	}
	data->env = tmp;
	return (tmp);
}

int	ft_list_cmp(t_data *data, char *var_env)
{
	t_elist	*tmp;

	tmp = data->env;
	while (data->env)
	{
		if (ft_strcmp(data->env->name, var_env) == 0)
			return (0);
		else
			data->env = data->env->next;
	}
	data->env = tmp;
	return (1);
}

void	ft_update_list(t_data *data, char *new_def, char *var_env)
{
	data->env = ft_search_node(data, var_env);
	if (data->env != NULL)
	{
		free(data->env->def);
		data->env->def = ft_strdup(new_def);
	}
	data->env = ft_first_node(data->env);
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
					curr->next->prev = curr->prev;
			}
			free(curr);
		}
		curr = curr->next;
	}
}
