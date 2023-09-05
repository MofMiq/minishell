/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:14:05 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/05 17:03:18 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_data *data, char **args)
{
	(void)args;
	if (data->argc == 1)
		ft_print_list(data->env, NULL, 1);
	else
	{
		if (chdir(data->args[1]) == 0)
			printf("%s: %s: %s\n", args[0], args[1], strerror(EACCES));
		else
			printf("%s: %s: %s\n", args[0], args[1], strerror(ENOENT));
	}
}

/*Belen no te asustes por este mamotraco de funcion, funciona perfe pero se
me ha tragantado a la hora de intentar acortarla*/

int	ft_check_name(char *name)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_mini_split(name, '=');
	while (split[0][i] != '\0')
	{
		// if (split[0][0] == '$')
		// {
		// 	printf("toy aqui!!!!!\n");
		// 	break ;
		// }
		if ((ft_isalpha(split[0][0]) == 0))
		{
			printf("bash: export: %s: not a valid identifer\n", name); //perror("export");
			ft_free_double_pointer(split);
			return (0);
		}
		else if (ft_isalnum(split[0][i]) == 0)
		{
			printf("bash: export: %s: not a valid identifer\n", name);
			ft_free_double_pointer(split);
			return (0);
		}
		i++;
	}
	ft_free_double_pointer(split);
	return (1);
}

void	ft_export(t_data *data)
{
	int		i;

	i = 1;
	if (data->argc == 1)
		ft_print_list(data->env, data->exp, 2);
	else
	{
		while (data->args[i] && ft_check_name(data->args[i]) == 1)
		{
			if (ft_strchr(data->args[i], '='))
			{
				if (data->exp)
					if (ft_list_cmp(data->exp, data->args[i]))
						ft_cmp_and_update(data, data->args[i], 2);
				ft_cmp_and_update(data, data->args[i], 1);
			}
			else
			{
				if (ft_list_cmp(data->exp, data->args[i]))
					ft_export_list(&data->exp, data->args[i]);
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
