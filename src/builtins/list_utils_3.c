/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:46:15 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/26 19:50:15 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export_list(t_elist **exp_lst, char *var_name)
{
	ft_add_back(exp_lst, ft_new_node(&var_name));
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

void	ft_print_list(t_data *data, t_elist *env, t_elist *exp, int i)
{
	t_elist	*tmp;
	t_elist	*aux;

	tmp = env;
	aux = exp;
	while (env)
	{
		if (i == 1)
		{
			ft_putstr_fd(env->name, data->fdout);
			ft_putchar_fd('=', data->fdout);
			ft_putstr_fd(env->def, data->fdout);
			ft_putchar_fd('\n', data->fdout);
			//printf("%s=%s\n", env->name, env->def);
		}
		else if (i == 2)
		{
			ft_putstr_fd("declare -x ", data->fdout);
			ft_putstr_fd(env->name, data->fdout);
			ft_putchar_fd('=', data->fdout);
			ft_putstr_fd(env->def, data->fdout);
			ft_putchar_fd('\n', data->fdout);
			//printf("declare -x %s=\"%s\"\n", env->name, env->def);
		}
		env = env->next;
	}
	env = tmp;
	if (i == 2)
	{
		while (exp)
		{
			ft_putstr_fd("declare -x ", data->fdout);
			ft_putstr_fd(exp->name, data->fdout);
			ft_putchar_fd('\n', data->fdout);
			//printf("declare -x %s\n", exp->name);
			exp = exp->next;
		}
	}
	exp = aux;
}

// void	ft_print_list(t_data *data, t_elist *exp, int i)
// {
// 	t_elist	*tmp;
// 	t_elist	*aux;

// 	tmp = env;
// 	aux = exp;
// 	while (env)
// 	{
// 		if (i == 1)
// 		{
// 			ft_putstr_fd(env->name, data->fdout);
// 			ft_putchar_fd('=', data->fdout);
// 			ft_putstr_fd(env->def, data->fdout);
// 			ft_putchar_fd('\n', data->fdout);
// 			//printf("%s=%s\n", env->name, env->def);
// 		}
// 		else if (i == 2)
// 		{
// 			ft_putstr_fd("declare -x ", data->fdout);
// 			ft_putstr_fd(env->name, data->fdout);
// 			ft_putchar_fd('=', data->fdout);
// 			ft_putstr_fd(env->def, data->fdout);
// 			ft_putchar_fd('\n', data->fdout);
// 			//printf("declare -x %s=\"%s\"\n", env->name, env->def);
// 		}
// 		env = env->next;
// 	}
// 	env = tmp;
// 	if (i == 2)
// 	{
// 		while (exp)
// 		{
// 			ft_putstr_fd("declare -x ", data->fdout);
// 			ft_putstr_fd(exp->name, data->fdout);
// 			ft_putchar_fd('\n', data->fdout);
// 			//printf("declare -x %s\n", exp->name);
// 			exp = exp->next;
// 		}
// 	}
// 	exp = aux;
// }
