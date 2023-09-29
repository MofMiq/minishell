/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:30:15 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/29 17:43:01 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*me acabo de hacer aqui una guarrada (32-38) y meto un nodo "vacio" para que
como en bash imprema un espacio "extra"*/

t_token	*ft_new_token(char *input, int i, int start)
{
	char	*tmp;
	t_token	*token;

	token = NULL;
	tmp = ft_substr(input, start, i - start);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		perror("Allocation problem\n");
		exit(EXIT_FAILURE);
	}
	if ((tmp[0] == '\"' && tmp[1] == '\"' && tmp[2] == '\0')
		|| (tmp[0] == '\'' && tmp[1] == '\'' && tmp[2] == '\0'))
	{
		free(tmp);
		tmp = ft_calloc(1, 1);
	}
	token->str = tmp;
	token->type = -1;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*ft_last_token(t_token *token)
{
	while (token && token->next != NULL)
		token = token->next;
	return (token);
}
//en pruebas
// t_token	*ft_first_token(t_token **token)
// {
// 	while ((*token) && (*token)->prev != NULL)
// 	{
// 		printf("en ft_first_token: token->str: %s\n", (*token)->str);
// 		(*token) = (*token)->prev;
// 	}
// 	return ((*token));
// }

t_token	*ft_penultimate_token(t_token *token)
{
	while (token->next->next != NULL)
		token = token->next;
	return (token);
}

t_token	*ft_add_token(t_token **token, t_token *new)
{
	if (!new)
		return (NULL);
	if (*token == NULL)
		*token = new;
	else
	{
		ft_last_token(*token)->next = new;
		if ((*token)->prev == NULL)
			new->prev = ft_penultimate_token(*token);
	}
	return (*token);
}
