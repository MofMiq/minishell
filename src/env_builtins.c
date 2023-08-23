/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:14:05 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/23 18:24:14 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_data *data, char **args)
{
	t_elist	*tmp;

	tmp = data->env;
	if (data->argc == 1)
	{
		while (data->env)
		{
			if (data->bool_exp == 1)
				printf("declare -x ");
			printf("%s=%s\n", data->env->name, data->env->def);
			data->env = data->env->next;
		}
	}
	else
	{
		//perror("env");
		printf("%s: %s: No such file or directory\n", args[0], args[1]);
		//liberar memorira
	}
	data->env = tmp;
}

void	ft_export(t_data *data)
{
	char	**splited;

	if (data->argc == 1)
	{
		data->bool_exp = 1;
		ft_env(data, data->args); //comillas para export
		data->bool_exp = 0;
	}
	else
	{
		if (ft_strchr(data->args[1], '='))
		{
			//cuidado ""
			splited = ft_split(data->args[1], '=');
			ft_add_back(&data->env, ft_new_node(splited));
		}
	}
}

void	ft_unset(t_elist *env, t_data *data)
{
	//poner en funcionamiento env->prev
	t_elist	*curr;
	t_elist	*prev;
	int		i;

	if (data->argc > 1)
	{
		i = 1;
		while (data->args[i] != NULL)
		{
			prev = NULL;
			curr = env;
			while (curr)
			{
				if (ft_strcmp(curr->name, data->args[i]) == 0)
				{
					if (prev == NULL)
						env = curr->next;
					else
						prev->next = curr->next;
					free(curr);
				}
				prev = curr;
				curr = curr->next;
			}
			i++;
		}
	}
}

/*void	ft_unset(t_data *data)
{
	t_elist	*curr;
	t_elist	*head;
	int	i;

	if (data->env == NULL)
		return ;
	if (data->argc > 1)
	{
		curr = data->env;
		head = data->env;
		i = 0;
		while (data->args[i] && curr)
		{
			if ((ft_strcmp(data->env->name, data->args[i])) != 0)
			{
				curr = curr->next;
				data->env = curr;
			}
			else
			{
				data->env = data->env->prev;
				data->env->next = curr->next;
				free(curr);
				i++;
				data->env = head;
			}
		}
	}
}*/
