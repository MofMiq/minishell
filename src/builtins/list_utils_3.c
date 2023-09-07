/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:46:15 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/07 10:14:50 by marirodr         ###   ########.fr       */
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
