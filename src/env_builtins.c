/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:14:05 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/01 10:04:23 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Reordenar este archivo, +5 funciones

void	ft_env(t_data *data, char **args)
{
	if (data->argc == 1)
		ft_print_list(data->env, NULL, 1);
	else
	{
		//perror("env");
		printf("%s: %s: No such file or directory\n", args[0], args[1]);
	}
}

void	ft_export_list(t_elist **exp_lst, char *var_name)
{
	ft_add_back(exp_lst, ft_new_node(&var_name));
}

void	ft_print_list(t_elist *env, t_elist *exp, int i)
{
	t_elist	*tmp;
	t_elist	*aux;

	tmp = env;
	aux = exp;
	while (env)
	{
		if (i == 1)
			printf("%s=%s\n", env->name, env->def);
		else if (i == 2)
			printf("declare -x %s=\"%s\"\n", env->name, env->def);
		env = env->next;
	}
	env = tmp;
	if (i == 2)
	{
		while (exp)
		{
			printf("declare -x %s\n", exp->name);
			exp = exp->next;
		}
	}
	exp = aux;
}

void	ft_export(t_data *data)
{
	char	**splited;
	int		i;

	i = 1;
	// data->bool_exp ya no sirve para nada
	if (data->argc == 1)
		ft_print_list(data->env, data->exp, 2);
	else
	{
		while (data->args[i])
		{
			if (ft_strchr(data->args[i], '='))
			{
				splited = ft_split(data->args[i], '=');
				if ((ft_list_cmp(data->env, splited[0])) == 0)
					ft_update_list(data->env, splited[1], splited[0]);
				else
					ft_add_back(&data->env, ft_new_node(splited));
				ft_free_double_pointer(splited);
			}
			else
			{
				ft_export_list(&data->exp, data->args[i]);
				//data->exp = ft_first_node(data->exp); no hace nada ajaja
			}
			i++;
		}
	}
}

void	ft_unset(t_elist **env, t_elist **exp, t_data *data)
{
	t_elist	*curr;
	t_elist	*curr2;
	int		i;

	if (data->argc > 1)
	{
		i = 1;
		while (data->args[i] != NULL)
		{
			curr = *env;
			curr2 = *exp;
			ft_remove_if(curr, data->args[i], env);
			ft_remove_if(curr2, data->args[i], exp);
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
				printf("bash: %s: %s: numeric argument is required\n", data->args[0], data->args[1]);
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
