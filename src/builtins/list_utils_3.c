/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:46:15 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/30 12:00:31 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export_list(t_elist **exp_lst, char *var_name)
{
	ft_add_back(exp_lst, ft_new_node(&var_name));
}

/*At the beginning of the program, we copy all the environmental variables with
this funcion. We split them from the equal sign in order to store the name and 
the definition separately in our linked list 'env', which makes it easier for
us to search and change them throughout the program's execution.*/

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

void	ft_print_env(t_data *data, t_elist *env, int i)
{
	t_elist	*tmp;

	tmp = env;
	while (env)
	{
		if (i == 1)
		{
			ft_putstr_fd(env->name, data->fdout);
			ft_putchar_fd('=', data->fdout);
			ft_putstr_fd(env->def, data->fdout);
			ft_putchar_fd('\n', data->fdout);
		}
		else if (i == 2)
		{
			ft_putstr_fd("declare -x ", data->fdout);
			ft_putstr_fd(env->name, data->fdout);
			ft_putchar_fd('=', data->fdout);
			ft_putstr_fd(env->def, data->fdout);
			ft_putchar_fd('\n', data->fdout);
		}
		env = env->next;
	}
	env = tmp;
	if (i == 2)
		ft_print_exp(data, data->exp);
}

void	ft_print_exp(t_data *data, t_elist *exp)
{
	t_elist	*aux;

	aux = exp;
	while (exp)
	{
		ft_putstr_fd("declare -x ", data->fdout);
		ft_putstr_fd(exp->name, data->fdout);
		ft_putchar_fd('\n', data->fdout);
		exp = exp->next;
	}
	exp = aux;
}
