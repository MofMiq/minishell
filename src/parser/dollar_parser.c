/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:09:16 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/17 17:31:55 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//ft_strchr(" \0\'\"" data->token->str[i + 1])

t_token	*ft_parse_dollar(t_data *data)
{
	t_token	*first;
	int		i;

	first = data->token;
	while (data->token)
	{
		i = 0;
		if (data->token->type != S_QUOTES)
		{
			while (data->token->str[i])
			{
				while (data->token->str[i] && data->token->str[i] != '$')
					i++;
				if (data->token->str[i] && data->token->str[i] == '$'
					&& (data->token->str[i + 1] == ' '
						|| data->token->str[i + 1] == '\0'))
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
	char	*ndef;

	s = ++(*i);
	if ((*token)->str[s] == '?')
		ndef = ft_exit_status(data->exit_status, i);
	else
	{
		while ((*token)->str[*i] && !ft_strchr(" $=\'\"", (*token)->str[*i]))
			(*i)++;
		cenv = ft_substr((*token)->str, s, (*i) - s);
		if (!ft_list_cmp(data->env, cenv))
		{
			aux = ft_search_node(data->env, cenv);
			ndef = ft_strdup(aux->def);
		}
		else
			ndef = ft_calloc(1, 1);
		free(cenv);
	}
	ft_change_dollar(&data->token, ndef, s - 1, *i);
	(*i) = s - 1;
	free(ndef);
}

/*a esta funcion hay que pasarle otro numero, que será un codigo de salida
que no se muy bien de donde lo obtendremos, pero que perfectamente podriamos
guardar en 'data' para que lo pueda pasar por aqui.
añadir data como argumento, o data->exit_status

$? solo en la linea de comando, abre un proceso nuevo?*/

char	*ft_exit_status(int exit_status, int *i)
{
	char	*ndef;

	(void)exit_status;
	ndef = ft_itoa(77777); //esto en un valor falso de prueba
	(*i)++;
	return (ndef);
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

int	ft_is_all_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
