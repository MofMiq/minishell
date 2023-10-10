/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:49:30 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/10 11:29:26 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sub_red(t_data *data, int *i, int *start, char c)
{
	if (c == '|' && data->input[(*i) + 1] != c)
		(*i)++;
	else if (c == '<' || c == '>')
	{
		while (ft_strchr("<>", data->input[*i]))
			(*i)++;
		while (data->input[*i] == ' ' && data->input[*i])
			(*i)++;
		while (data->input[*i] != ' ' && data->input[*i])
			(*i)++;
	}
	ft_add_token(&data->token, ft_new_token(data->input, *i, *start));
}

/*esta funcion es unaa real mierda
Añadir casos como los que me dijo juan: <> ó ><, >   >, <   <,   >  | */

int	ft_bad_redi(t_token *token, int fd)
{
	t_token	*aux;

	aux = token;
	while (aux)
	{
		if (aux->type == APPEND && ft_strncmp(aux->str, ">>>", 3) == 0)
		{
			ft_putstr_fd("syntax error near unexpected token\n", fd);
			return (1);
		}
		else if (aux->type == HERE_DOC && ft_strncmp(aux->str, "<<<", 3) == 0)
		{
			ft_putstr_fd("syntax error near unexpected token\n", fd);
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}

int	ft_is_redi(t_token *token)
{
	t_token	*aux;

	aux = token;
	while (aux)
	{
		if (aux->type >= OUT && aux->type <= HERE_DOC)
			return (1);
		aux = aux->next;
	}
	return (0);
}
