/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:09:16 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/19 18:49:17 by marirodr         ###   ########.fr       */
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
					while (data->token->str[i] && (ft_strchr(" $=", data->token->str[i]) == NULL))
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
					if (cdef[0] != '\0')
						free(cdef);
				}
			}
		}
		data->token = data->token->next;
	}
	data->token = first;
	return (data->token);
}
