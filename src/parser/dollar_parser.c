/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:09:16 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/20 18:42:57 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_parse_dollar(t_data *data)
{
	t_token	*first;
	int		i;

	first = data->token;
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
					ft_dollar_aux(data, &data->token, &i);
			}
		}
		data->token = data->token->next;
	}
	data->token = first;
	return (data->token);
}

void	ft_dollar_aux(t_data *data, t_token **token, int *i)
{
	t_elist	*aux;
	int		s;
	char	*cenv;
	char	*cdef;

	(*i)++;
	s = *i;
	while ((*token)->str[*i] && (ft_strchr(" $=", (*token)->str[*i]) == NULL))
		(*i)++;
	cenv = ft_substr((*token)->str, s, (*i) - s);
	if (!ft_list_cmp(data->env, cenv))
	{
		aux = ft_search_node(data->env, cenv);
		cdef = ft_strdup(aux->def);
	}
	else
		cdef = "";
	ft_change_dollar(&data->token, cdef, s - 1, *i);
	free(cenv);
	if (cdef[0] != '\0')
		free(cdef);
}

void	ft_change_dollar(t_token **token, char *nstr, int drop, int take)
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
