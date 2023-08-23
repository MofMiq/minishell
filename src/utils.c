/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:25 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/23 16:08:01 by begarijo         ###   ########.fr       */
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

t_elist	*ft_list_cmp(t_data *data, char *var_env)
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
