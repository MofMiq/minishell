/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rejoin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:45:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/02 15:15:52 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*esta funcion es un simple parche para un problema mas grande.
en el parseo divido por espacios y tokenizo pero a la hora de imprimir
creo que vamos a tener un problema porque pierdo la referencias de los
espacios y ya no sabemos si esas cosas van juntas o no.
tengo que darle una vuelta.*/

int	ft_check_join(t_token *token)
{
	t_token	*aux;

	aux = token;
	while (aux)
	{
		if (aux->join == 0)
			return (1);
		aux = aux->next;
	}
	return (0);
}

void	ft_del_token(t_token *node)
{
	free(node->str);
	node->next = NULL;
	node->prev = NULL;
	free(node);
}

void	ft_rejoin(t_token **token)
{
	char	*tmp;
	t_token	*first;
	t_token	*del;
	t_token	*new;

	first = (*token);
	while (*token)
	{
		if ((*token)->join == 0)
		{
			del = (*token);
			printf("%s---------%s\n", PINK, END);
			printf("en ft_rejoin: del->str: %s\n", del->str);
			tmp = ft_strjoin((*token)->str, (*token)->next->str);
			printf("en ft_rejoin: tmp despues de joins: %s\n", tmp);
			new = ft_new_token(tmp, ft_strlen(tmp), 0);
			new->type = NO_QUOTES;
			printf("en ft_rejoin: new: str: %s / join: %d\n", new->str, new->join);
			(*token)->prev->next = new;
			new->next = del->next->next;
			if (del->next->join == 0)
				new->join = 0;
			ft_del_token(del->next);
			ft_del_token(del);
			free(tmp);
			(*token) = first;
			return ;
			//printf("en ft_rejoin: (*token): str: %s / join: %d\n", (*token)->str, (*token)->join);
		}
		(*token) = (*token)->next;
	}
	(*token) = first;
	// while (*token)
	// {
	// 	printf("en buclecito ft_rejoin: (*token): str: %s / join: %d\n", (*token)->str, (*token)->join);
	// 	(*token) = (*token)->next;
	// }
	// (*token) = first;
}

// void	ft_rejoin(t_data *data)
// {
// 	char	*tmp;
// 	t_token	*aux;
// 	t_token	*del;
// 	t_token	*new;

// 	aux = data->token;
// 	while (data->token)
// 	{
// 		if (data->token->join == 0)
// 		{
// 			del = data->token;
// 			printf("en ft_rejoin: del->str: %s\n", del->str);
// 			tmp = ft_strjoin(data->token->str, data->token->next->str);
// 			printf("en ft_rejoin: tmp despues de joins: %s\n", tmp);
// 			new = ft_new_token(tmp, ft_strlen(tmp), 0);
// 			new->type = NO_QUOTES;
// 			printf("en ft_rejoin: new: str: %s / join: %d\n", new->str, new->join);
// 			data->token->prev->next = new;
// 			new->next = del->next->next;
// 			ft_del_token(del->next);
// 			ft_del_token(del);
// 			free(tmp);
// 		}
// 		data->token = data->token->next;
// 	}
// 	data->token = aux;
// 	while (data->token)
// 	{
// 		printf("en ft_rejoin: data->token: str: %s / join: %d\n", data->token->str, data->token->join);
// 		data->token = data->token->next;
// 	}
// 	data->token = aux;
// }
