/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:14:05 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/30 17:14:10 by marirodr         ###   ########.fr       */
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
			if ((ft_list_cmp(data->env, splited[0])) == 0)
				ft_update_list(data->env, splited[1], splited[0]);
			else
				ft_add_back(&data->env, ft_new_node(splited));
			ft_free_double_pointer(splited);
		}
	}
}

void	ft_unset(t_elist **env, t_data *data)
{
	t_elist	*curr;
	int		i;

	if (data->argc > 1)
	{
		i = 1;
		while (data->args[i] != NULL)
		{
			curr = *env;
			ft_remove_if(curr, data->args[i], env);
			i++;
		}
	}
}

void	ft_miniexit(t_data *data)
{
	int	i;

	i = 0;
	if ((ft_strcmp(data->args[0], "exit")) == 0)
	{
		if (data->args[1])
		{
			if (ft_atoi(data->args[1]) != 0)
			{
				printf("%s\n", data->args[0]);
				ft_free_all(data);
				exit(EXIT_FAILURE);
			}
			if (!ft_isdigit(data->args[1][0]))
			{
				printf("bash: %s: %s: numeric argument is required\n", data->args[0], data->args[1]); //hacer funcion adecuada a perror
				ft_free_all(data);
				exit(EXIT_FAILURE);
			}
		}
		printf("%s\n", data->args[0]);
		ft_free_all(data);
		exit(EXIT_SUCCESS);
	}
}

t_elist	*ft_copy_env(char **env)
{
	int		i;
	char	**splited;
	t_elist	*elist;

	i = 0;
	elist = NULL;
	while (env[i])
	{
		splited = ft_mini_split(env[i], '=');
		ft_add_back(&elist, ft_new_node(splited));
		i++;
		ft_free_double_pointer(splited);
	}
	return (elist);
}
