/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:49:30 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/13 16:54:57 by marirodr         ###   ########.fr       */
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

int	ft_check_syntax(t_token *aux) // en pruebas
{
	int	i;

	i = 0;
	printf("--llego a fT_check_syntack--y aux:_str: %s\n", aux->str);
	if ((aux->type >= OUT && aux->type <= APPEND) && (aux->next->type == PIPE))
	{
		while (aux->str[i])
		{
			printf("--salgo de fT_check_syntack\n");
			if (ft_isalpha_plus(aux->str[i]) == 1) //al reves
				return (1);
			i++;
		}
	}
	return (0);
}

/*mirar esto con mas detenimiento cuando se arregle mas cosas de pipeline*/

int	ft_bad_redi(t_token *token, int fd)
{
	t_token	*aux;

	aux = token;
	while (aux)
	{
		// if (((aux->type >= PIPE && aux->type <= HERE_DOC) && (aux->next && aux->next->type >= PIPE && aux->next->type <= HERE_DOC)))
		// {
		// 	ft_putstr_fd("syntax ERROR near unexpected token\n", fd);
		// 	return (1);
		// }
		if (aux->type == PIPE && (aux->next && aux->next->type >= PIPE && aux->next->type <= HERE_DOC))
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
