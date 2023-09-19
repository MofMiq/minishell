/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:09:16 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/19 18:05:52 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_dollar_aux(t_token **token, char *nstr, int drop, int take)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char) * (ft_strlen((*token)->str)) \
	- (take - drop) + ft_strlen(nstr));
	if (!copy)
		return ;
	while (i < drop)
		copy[i++] = (*token)->str[j++];
	j = 0;
	while (nstr[j])
		copy[i++] = nstr[j++];
	j = take;
	while ((*token)->str[j])
		copy[i++] = (*token)->str[j++];
	copy[i] = '\0';
	free((*token)->str);
	(*token)->str = ft_strdup(copy);
	free(copy);
}

t_token	*ft_parse_dollar(t_data *data)
{
	t_token	*first;
	t_elist	*aux;
	char	*cenv;
	char	*cdef;
	int		s;
	int	i;

	first = data->token;
	// if (data->token->next) //esto lo tengo que controlar en condi
	data->token = data->token->next;
	while (data->token)
	{
		if (data->token->type != S_QUOTES)
		{
			while (ft_strchr(data->token->str, '$'))
			{
				i = 0;
				while (data->token->str[i] && data->token->str[i] != '$')
					i++;
				if (data->token->str[i] == '$')
				{
					i++;
					s = i;
					while (data->token->str[i] && (ft_strchr(" ", data->token->str[i]) == NULL))
						i++;
					cenv = ft_substr(data->token->str, s, i - s);
					if (!ft_list_cmp(data->env, cenv))
					{
						aux = ft_search_node(data->env, cenv);
						cdef = ft_strdup(aux->def);
					}
					else
						cdef = "";
					ft_dollar_aux(&data->token, cdef, s - 1, i);
					free(cenv);
					//printf("%sft_dollar token->str: %s%s\n", PINK, data->token->str, END);
					free(cdef);
				}
			}
		}
		data->token = data->token->next;
	}
	data->token = first;
	return (data->token);
}
// t_token	*ft_parse_dollar(t_data *data)
// {
// 	char	**tmp;
// 	t_token	*first;
// 	int		d;

// 	first = data->token;
// 	// if (data->token->next) //esto lo tengo que controlar en condi
// 	data->token = data->token->next;
// 	while (data->token)
// 	{
// 		d = 0;
// 		if (ft_strchr(data->token->str, '$') && data->token->type != S_QUOTES)
// 		{
// 			tmp = ft_split(data->token->str, '$');
// 			while (tmp[d])
// 			{
// 				ft_dollar_aux(data, d, &data->token, tmp[d]);
// 				d++;
// 			}
// 			ft_free_double_pointer(tmp);
// 		}
// 		data->token = data->token->next;
// 	}
// 	data->token = first;
// 	return (data->token);
// }

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
