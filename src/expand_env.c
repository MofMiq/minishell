/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:47:40 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/05 17:41:20 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*esto esta en fase testeo, no hasgas mucho caso*/

void	ft_find_dollar(char **args, t_elist *env)
{
	int			i;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;
	char		*tmp4;
	t_elist		*aux;
	char		**split;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '$'))
		{
			tmp = ft_strchr(args[i], '$');
			tmp++;
			printf("en ft_find_dolar: tmp: %s\n", tmp);
			if (ft_strchr(args[i], '='))
			{
				split = ft_mini_split(tmp, '=');
				tmp = split[0];
				tmp2 = ft_strjoin("=", split[1]);
				printf("en ft_find_dolar despues split: tmp: %s\n", tmp);
				printf("en ft_find_dolar despues split: tmp2: %s\n", tmp2);
				if (ft_list_cmp(env, /*++*/tmp) == 0)
				{
					aux = ft_search_node(env, tmp);
					free(args[i]);
					tmp3 = ft_strdup(aux->def);
					printf("en ft_find_dolar: tmp3: %s\n", tmp3);
					tmp4 = ft_strjoin(tmp3, tmp2);
					printf("en ft_find_dolar: tmp4: %s\n", tmp4);
					args[i] = tmp3;
				}
				//free(tmp3);
				free(tmp2);
				free(tmp4);
				ft_free_double_pointer(split);
			}
			else if (ft_list_cmp(env, /*++*/tmp) == 0)
			{
				aux = ft_search_node(env, tmp);
				free(args[i]);
				args[i] = ft_strdup(aux->def);
			}
		}
		i++;
	}
}
