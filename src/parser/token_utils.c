/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:47 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/26 16:31:33 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_join_glued_tokes(t_data *data)
{
	t_token	*tmp;
	t_token	*curr;

	tmp = data->token;
	data->token = data->token->next;
	while (data->token)
	{
		if ((data->token->type >= 1 && data->token->type <= 4)
			&& data->token->space == 0
			&& (data->token->prev->type >= 1 && data->token->prev->type <= 4))
		{
			data->token->prev->str = ft_strjoin_gnl(data->token->prev->str, \
			data->token->str);
			if (!data->token->prev->prev && data->token->prev->type == BUILTIN)
				data->token->type = NO_QUOTES;
			curr = data->token;
			ft_remove_if_token(curr, curr->str, &data->token, 1);
		}
		data->token = data->token->next;
	}
	data->token = tmp;
	if (!ft_is_builtin(data->token->str))
		data->token->type = NO_QUOTES;
	else
		data->token->type = BUILTIN;
}
/*i = 0; elimina toda la lista, todas la coincidencias &&
i = 1 elimina solo un nodo y salte*/

void	ft_remove_if_token(t_token *curr, char *cstr, t_token **token, int i)
{
	while (curr)
	{
		if (ft_strcmp(curr->str, cstr) == 0)
		{
			if (curr->prev == NULL)
			{
				*token = curr->next;
				if (*token)
					(*token)->prev = NULL;
			}
			else
			{
				curr->prev->next = curr->next;
				if (curr->next)
					curr->next->prev = curr->prev;
			}
			free(curr->str);
			free(curr);
		}
		if (i == 0)
			curr = curr->next;
		if (i == 1)
			return ;
	}
}

void	ft_reconvert_token(t_data *data)
{
	t_token	*tmp;
	int		i;

	i = ft_token_size(data);
	data->argc = i;
	data->args = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!data->args)
		return ;
	tmp = data->curr_tkn;
	i = 0;
	while (tmp)
	{
		if (tmp->type >= PIPE && tmp->type <= HERE_DOC)
			break ;
		data->args[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
}

int	ft_token_size(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->curr_tkn;
	i = 0;
	while (tmp)
	{
		if (tmp->type >= PIPE && tmp->type <= HERE_DOC)
			break ;
		else
		{
			i++;
			tmp = tmp->next;
		}
	}
	return (i);
}

/*Returns the number of pipe in the input, without being between quotes*/

int	ft_count_pipes(t_token *token)
{
	int		c;
	t_token	*tmp;

	c = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			c++;
		tmp = tmp->next;
	}
	return (c);
}
