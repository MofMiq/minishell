/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:25 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/24 16:58:51 by marirodr         ###   ########.fr       */
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

//hacer otra fucnion booleana que sea de comparacion
t_elist	*ft_list_cmp(t_data *data, char *var_env) //cambiar el nombre ft_update node
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
