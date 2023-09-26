/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:49:30 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/25 10:50:41 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_redirections(t_data *data, int *i, int *start, char c)
{
	if (c == '|' && data->input[(*i) + 1] != c)
		(*i)++;
	else if (c == '<' || c == '>')
	{
		while (ft_strchr("<>", data->input[*i]))
			(*i)++;
	}
	ft_add_token(&data->token, ft_new_token(data->input, *i, *start));
}

/*esta funcion es unaa real mierda*/

int	ft_bad_redi(t_token *token)
{
	t_token	*aux;

	aux = token;
	while (aux)
	{
		if (aux->type == D_GREAT && ft_strlen(aux->str) >= 3)
		{
			printf("syntax error near unexpected token\n");
			return (1);
		}
		else if (aux->type == D_LESS && ft_strlen(aux->str) >= 4)
		{
			printf("syntax error near unexpected token\n");
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}
