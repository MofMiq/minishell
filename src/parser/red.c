/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:49:30 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/10 18:35:42 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sub_red(t_data *data, int *i, int *start, char c)
{
	if (c == '|' && data->input[(*i) + 1] != c)
		(*i)++;
	else if (c == '<' || c == '>')
	{
		while (data->input[*i] == c)
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

int	ft_bad_syntax(t_token *aux)
{
	int	i;

	if (aux->type == OUT || aux->type == IN)
		i = 1;
	if (aux->type == APPEND || aux->type == HERE_DOC)
		i = 2;
	while (aux->str[i])
	{
		if (aux->str[i] == '>' || aux->str[i] == '<' || aux->str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	ft_bad_redi(t_token *token, int fd)
{
	t_token	*aux;

	aux = token;
	while (aux)
	{
		if ((aux->type >= PIPE && aux->type <= HERE_DOC)
			&& (aux->next && aux->next->type >= PIPE
				&& aux->next->type <= HERE_DOC))
		{
			ft_putstr_fd("syntax ERROR near unexpected token\n", fd);
			return (1);
		}
		if ((aux->type == APPEND && ft_strncmp(aux->str, ">>>", 3) == 0)
			|| (aux->type == HERE_DOC && ft_strncmp(aux->str, "<<<", 3) == 0)
			|| ft_bad_syntax(aux))
		{
			ft_putstr_fd("syntax error near unexpected token\n", fd);
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}
