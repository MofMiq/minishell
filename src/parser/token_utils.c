/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:30:15 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/08 16:43:32 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_new_token(char *input, int i, int start)
{
	char	*tmp;
	t_token	*token;

	tmp = ft_substr(input, start, i - start);
	//printf ("en ft_new_token: str: %s\n", tmp);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		perror("Allocation problem\n");
		exit(EXIT_FAILURE);
	}
	token->str = tmp;
	token->type = -1;
	token->next = NULL;
	token->prev = NULL;
	//printf ("en ft_new_token: token->str: %s\n", token->str);
	return (token);
}

t_token	*ft_last_token(t_token *token)
{
	while (token && token->next != NULL)
		token = token->next;
	return (token);
}

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
