/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:14:05 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/23 12:17:56 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_data *data, char **args)
{
	t_elist	*tmp;

	tmp = data->env;
	if (args[1] == NULL)
	{
		while (data->env)
		{
			if (data->bool_exp == 1)
				printf("declare -x ");
			printf("%s=%s\n", data->env->name, data->env->def);
			data->env = data->env->next;
		}
	}
	data->env = tmp;
//	else
//		perror("env");
//	ARREGLEMOS ESTO PORFIS
}

void	ft_export(t_data *data)
{
	if (data->args[1] == NULL)
	{
		data->bool_exp = 1;
		ft_env(data, data->args); //comillas para export
		data->bool_exp = 0;
	}
}
