/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:19:45 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/20 18:44:14 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_quotes(t_data *data, int *i, int *start, char q)
{
	if (data->input[*i] == q)
		(*i)++;
	while (data->input[*i] != q)
		(*i)++;
	if (data->input[*i] == q && (data->input[(*i) + 1] == ' '
			|| data->input[(*i) + 1] == '\0'))
		(*i)++;
	ft_add_token(&data->token, ft_new_token(data->input, *i, *start));
}

void	ft_ignore_quotes(t_data *data)
{
	t_token	*tmp;
	char	*copy;
	int		i;
	int		j;
	int		len;

	tmp = data->token;
	while (data->token)
	{
		if (data->token->type == S_QUOTES || data->token->type == D_QUOTES)
		{
			i = 0;
			j = 0;
			len = (ft_strlen(data->token->str) - ft_c_quotes(data->token->str));
			copy = ft_calloc(len + 1, sizeof(char));
			copy = ft_copy_no_quotes(data->token->str, copy, i, j);
			free(data->token->str);
			data->token->str = NULL;
			data->token->str = ft_strdup(copy);
			free(copy);
		}
		data->token = data->token->next;
	}
	data->token = tmp;
}

char	*ft_copy_no_quotes(char *token, char *copy, int i, int j)
{
	while (token[i])
	{
		if ((ft_strchr("'\"''\''", (token[i])) == NULL))
				copy[j++] = token[i++];
		else
			i++;
	}
	return (copy);
}

int	ft_c_quotes(char *str)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			c++;
		i++;
	}
	return (c);
}

int	ft_is_closed(char *str, char c)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == c)
			q++;
		i++;
	}
	return (q);
}