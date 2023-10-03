/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:47 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/03 11:43:38 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_token_cat(t_token *aux, t_token *first, int len, int i)
{
	char	*tmp;

	while (aux && aux->space == 0)
	{
		len += ft_strlen(aux->str);
		aux = aux->next;
	}
	tmp = ft_calloc(len, sizeof(char));
	while (first && first->space == 0)
	{
		len = 0;
		while (first->str[len])
			tmp[i++] = first->str[len++];
		first = first->next;
	}
	return (tmp);
}
/*mirar con detenimiento*/

int	ft_one_bad_arg(t_data *data)
{
	int		len;
	char	*tmp;
	t_token	*aux;
	t_token	*first;

	len = ft_strlen(data->token->str);
	aux = data->token;
	first = data->token;
	if (data->input[len] == '\0' || data->input[len] == ' ')
		return (0);
	if (ft_strchr("'\''\"", data->token->str[len]))
	{
		tmp = ft_token_cat(aux->next, first, len, 0);
		printf("bash: %s: command not found\n", tmp);
		free(tmp);
		return (1);
	}
	return (0);
}