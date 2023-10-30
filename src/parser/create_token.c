/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:30:15 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/30 14:11:58 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* With this function, we create a node for each token in the input. We have its
start and end from the ft_divide_input(), ft_subdivide_input(), ft_quotes() and
ft_sub_red().

We have added a filed called 'space' which is going to be very useful in the
future to know if a token should be joined with another one. That is done by
checking if there is a space before the 'start' position in the input, except
for quoted tokens, as that doesn't work. We have done some weird thing that
maybe we could have done differently and more clearly. 
1 is for whe there's a space; 0 if not.

All the functions in this file are for the creation of the list.*/

t_token	*ft_new_token(char *input, int i, int start, t_data *data)
{
	char	*tmp;
	t_token	*token;

	tmp = ft_substr(input, start, i - start);
	if (!ft_strcmp(tmp, "\"\"") || !ft_strcmp(tmp, "\'\'"))
	{
		free(tmp);
		if (input[start - 1] == ' ')
			data->aux_space = 1;
		return (NULL);
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		perror("Allocation problem\n");
		exit(EXIT_FAILURE);
	}
	token->str = tmp;
	token->type = -1;
	if (data->aux_space == 1)
		token->space = 1;
	else
		token->space = ft_check_space(input[start - 1]);
	data->aux_space = -1;
	return (token->next = NULL, token->prev = NULL, token);
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

int	ft_check_space(char c)
{
	if (c != ' ')
		return (0);
	return (1);
}
