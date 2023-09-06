/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:47:40 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/06 13:33:38 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*este archivo es para las variables de entorno, funciona pero con pinzas y
probablemente con errores inesperados.
va ha haber que repensarlo y cambiarlo segun el parseo*/

char	*ft_dollar_and_equal(char *str, t_elist *lst, char *arg)
{
	char	**split;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	t_elist	*aux;

	split = ft_mini_split(str, '=');
	str = split[0];
	tmp = ft_strjoin("=", split[1]);
	if (ft_list_cmp(lst, str) == 0)
	{
		aux = ft_search_node(lst, str);
		free(arg);
		tmp2 = ft_strdup(aux->def);
		tmp3 = ft_strjoin(tmp2, tmp);
		arg = tmp3;
		free(tmp2);
	}
	free(tmp);
	ft_free_double_pointer(split);
	return (arg);
}

char	*ft_equal_and_dollar(char *str, t_elist *lst, char *arg)
{
	char	**split;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	t_elist	*aux;

	split = ft_mini_split(str, '=');
	str = split[1];
	str++;
	tmp = ft_strjoin(split[0], "=");
	if (ft_list_cmp(lst, str) == 0)
	{
		aux = ft_search_node(lst, str);
		free(arg);
		tmp2 = ft_strdup(aux->def);
		tmp3 = ft_strjoin(tmp, tmp2);
		arg = tmp3;
		free(tmp2);
	}
	free(tmp);
	ft_free_double_pointer(split);
	return (arg);
}

int	ft_where_equal(char *str)
{
	int	i;
	int	d;
	int	e;

	i = 0;
	d = 0;
	e = 0;
	if (ft_strchr(str, '='))
	{
		while (str[i])
		{
			if (str[i] == '$')
				d = i;
			else if (str[i] == '=')
				e = i;
			i++;
		}
		if (d < e)
			return (1);
		else if (e < d)
			return (2);
	}
	return (0);
}

void	ft_find_dollar(char **args, t_data *data)
{
	int			i;
	char		*tmp;
	t_elist		*aux;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '$'))
		{
			tmp = ft_strchr(args[i], '$');
			tmp++;
			printf("en ft_find_dolar: tmp: %s\n", tmp);
			if (ft_where_equal(args[i]) == 1/* && ft_strncmp(args[i], "export", 6)*/)
				args[i] = ft_dollar_and_equal(tmp, data->env, args[i]);
			else if (ft_where_equal(args[i]) == 2/* && ft_strncmp(args[i], "export", 6)*/)
				args[i] = ft_equal_and_dollar(args[i], data->env, args[i]);
			else if (!ft_where_equal(args[i]) && !ft_list_cmp(data->env, tmp))
			{
				aux = ft_search_node(data->env, tmp);
				free(args[i]);
				args[i] = ft_strdup(aux->def);
			}
		}
		i++;
	}
}
