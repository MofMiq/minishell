/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:09:16 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/12 17:39:43 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_dollar_aux(t_data *data, int d, t_token **token, char *tmp)
{
	t_elist	*aux;

	if (d == 0)
	{
		free((*token)->str);
		(*token)->str = NULL;
	}
	if (!ft_list_cmp(data->env, tmp))
	{
		aux = ft_search_node(data->env, tmp);
		(*token)->str = ft_strjoin_sl((*token)->str, aux->def);
	}
}

t_token	*ft_parse_dollar(t_data *data)
{
	char	**tmp;
	t_token	*first;
	int		d;

	first = data->token;
	// if (data->token->next) //esto lo tengo que controlar en condi
	data->token = data->token->next;
	while (data->token)
	{
		d = 0;
		if (ft_strchr(data->token->str, '$'))
		{
			tmp = ft_split(data->token->str, '$');
			while (tmp[d])
			{
				ft_dollar_aux(data, d, &data->token, tmp[d]);
				d++;
			}
			ft_free_double_pointer(tmp);
		}
		data->token = data->token->next;
	}
	data->token = first;
	return (data->token);
}

/*nominette cuidado*/

char	*ft_sub_env(t_data *data, char *str, int d, int len)
{
	char		*tmp;
	t_elist	*aux;

	if (ft_strncmp(str, "$", 1) == 0)
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 1);
		if (ft_list_cmp(data->env, tmp) == 0)
		{
			aux = ft_search_node(data->env, tmp);
			free(str); //dudas aqui
			free(tmp);
			str = ft_strdup(aux->def);
			return (str);
		}
	}
	if (d != len)
	{
		tmp = ft_strjoin(str, "=");
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		return (str);
	}
	return (str);
}

/*jaja lol esta funcion xdddd
mucho mejor pero tengo que seguir haciendo malabares*/

t_token *ft_dollar_export(t_data *data)
{
	char	**tmp;
	t_token	*first;
	int		d;

	first = data->token;
	// if (data->token->next) //esto lo tengo que controlar en condi
	data->token = data->token->next;
	while (data->token)
	{
		d = 0;
		if ((ft_strchr(data->token->str, '$'))
			&& (ft_strchr(data->token->str, '=')))
		{
			tmp = ft_old_split(data->token->str, '=');
			free(data->token->str);
			data->token->str = NULL;
			while (tmp[d])
			{
				tmp[d] = ft_sub_env(data, tmp[d], d, (ft_double_pointer_len(tmp) - 1));
				data->token->str = ft_strjoin_sl(data->token->str, tmp[d]);
				d++;
			}
			ft_free_double_pointer(tmp);
		}
		data->token = data->token->next;
	}
	data->token = first;
	return (data->token);
}
