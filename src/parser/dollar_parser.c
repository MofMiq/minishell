/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:09:16 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/13 12:36:59 by marirodr         ###   ########.fr       */
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

char	*ft_sub_env(t_data *data, char *str, int d, int len)
{
	char	*tmp;
	t_elist	*aux;

	if (ft_strncmp(str, "$", 1) == 0)
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 1);
		if (ft_list_cmp(data->env, tmp) == 0)
		{
			aux = ft_search_node(data->env, tmp);
			free(str); //dudas aqui; parece que chachi
			free(tmp);
			str = ft_strdup(aux->def);
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

void	ft_divide_dollar(t_data *data, t_token **token, int *d)
{
	char	**split;
	int		len;

	split = ft_old_split((*token)->str, '=');
	len = ft_double_pointer_len(split) - 1;
	free((*token)->str);
	(*token)->str = NULL;
	while (split[*d])
	{
		split[*d] = ft_sub_env(data, split[*d], *d, len);
		(*token)->str = ft_strjoin_sl((*token)->str, split[*d]);
		(*d)++;
	}
	ft_free_double_pointer(split);
}

t_token	*ft_dollar_export(t_data *data)
{
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
			ft_divide_dollar(data, &data->token, &d);
		data->token = data->token->next;
	}
	data->token = first;
	return (data->token);
}
