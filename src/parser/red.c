/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:49:30 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/26 16:01:15 by marirodr         ###   ########.fr       */
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
		while (data->input[*i] == ' ' && data->input[*i])
			(*i)++;
		while (data->input[*i] != ' ' && data->input[*i])
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
		if (aux->type == D_GREAT && ft_strncmp(aux->str, ">>>", 3) == 0)
		{
			printf("syntax error near unexpected token\n");
			return (1);
		}
		else if (aux->type == D_LESS && ft_strncmp(aux->str, "<<<", 3) == 0)
		{
			printf("syntax error near unexpected token\n");
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
		if (aux->type == GREAT || aux->type == D_GREAT
			|| aux->type == LESS || aux->type == D_LESS)
			return (1);
		aux = aux->next;
	}
	return (0);
}

void	ft_what_redi(t_data *data)
{
	t_token	*aux;

	aux = data->token;
	while (aux)
	{
		if (aux->type == GREAT)
			ft_redi_output(data, aux);
		else if (aux->type == D_GREAT)
			printf("hacer la redireccion del output con append\n");
		else if (aux->type == LESS)
			printf("hacer la redireccion del input\n");
		else if (aux->type == D_LESS)
			printf("hacer la redireccion del here-document input\n");
		aux = aux->next;
	}
}
