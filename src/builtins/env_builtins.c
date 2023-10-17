/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:14:05 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/16 18:15:02 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_data *data, char **args)
{
	(void)args;
	if (data->argc == 1)
		ft_print_env(data, data->env, 1);
	else
	{
		ft_putstr_fd(args[0], data->fdout);
		ft_putstr_fd(": ", data->fdout);
		ft_putstr_fd(args[1], data->fdout);
		ft_putstr_fd(": ", data->fdout);
		if (chdir(data->args[1]) == 0)
			ft_putstr_fd(strerror(EACCES), data->fdout);
		else
			ft_putstr_fd(strerror(ENOENT), data->fdout);
		ft_putchar_fd('\n', data->fdout);
	}
}

int	ft_check_name(char *name, t_data *data)
{
	int		i;
	char	**split;

	i = -1;
	if (name[0] == '=')
		return (ft_check_name_print(name, data));
	if (name[0] == '\0')
		return (0);
	else
	{
		split = ft_mini_split(name, '=');
		while (split[0][++i] != '\0')
		{
			if ((ft_isalpha_plus(split[0][0]) == 0))
			{
				ft_free_double_pointer(split);
				return (ft_check_name_print(name, data));
			}
			else if (ft_isalnum_plus(split[0][i]) == 0)
			{
				ft_free_double_pointer(split);
				return (ft_check_name_print(name, data));
			}
		}
		ft_free_double_pointer(split);
	}
	return (1);
}

void	ft_export(t_data *data)
{
	int		i;

	i = 1;
	if (data->argc == 1)
		ft_print_env(data, data->env, 2);
	else
	{
		while (data->args[i])
		{
			if (ft_check_name(data->args[i], data) == 0)
				i++;
			else
			{
				if (ft_strchr(data->args[i], '='))
				{
					if (data->exp)
						if (ft_list_cmp(data->exp, data->args[i]))
							ft_cmp_and_update(data, data->args[i], 2);
					ft_cmp_and_update(data, data->args[i], 1);
				}
				else
					if (ft_list_cmp(data->exp, data->args[i])
						&& ft_list_cmp(data->env, data->args[i]))
						ft_export_list(&data->exp, data->args[i]);
				i++;
			}
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
	if (data->args[1])
	{
		if (ft_atoi(data->args[1]) != 0)
		{
			ft_putstr_fd(data->args[0], data->fdout);
			ft_putchar_fd('\n', data->fdout);
			ft_free_all(data);
			exit(EXIT_FAILURE);
		}
		if (!ft_isdigit(data->args[1][0]))
		{
			ft_putstr_fd(data->args[0], data->fdout);
			ft_putchar_fd('\n', data->fdout);
			ft_putstr_fd("bash: ", data->fdout);
			ft_putstr_fd(data->args[0], data->fdout);
			ft_putstr_fd(": ", data->fdout);
			ft_putstr_fd(data->args[1], data->fdout);
			ft_putstr_fd(": numeric argument is required\n", data->fdout);
			exit(EXIT_FAILURE);
		}
	}
	if (data->lvl > 1)
	{
		ft_putstr_fd("exit", data->fdout);
		data->lvl -= 1;
	}
	else
	{
		//ft_putstr_fd("exit", data->fdout); //belen habiass borrado esta linea? te daba por culo en algun lado?? o despiste?
		ft_putchar_fd('\n', data->fdout);
		ft_free_all(data);
		exit(EXIT_SUCCESS);
	}
}
