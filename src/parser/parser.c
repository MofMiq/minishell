/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/08 11:48:33 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_new_token(char *input, int i, int start) //like ft_new_node
{
	char	*tmp;
	t_token	*token;

	tmp = ft_substr(input, start, i - start);
	printf ("en ft_new_token: str: %s\n", tmp);
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
	printf ("en ft_new_token: token->str: %s\n", token->str);
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

/*fucnion incompleta y erroenea totalmente, solo le he puesto lo de las
comillas, para pasar al else del tiron.*/

t_token	*ft_assign_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (data->token)
	{
		if (data->token->str[0] == '\'')
			data->token->type = S_QUOTES;
		else if (data->token->str[0] == '\"')
			data->token->type = D_QUOTES;
		else
			data->token->type = NO_QUOTES;
		data->token = data->token->next;
	}
	data->token = tmp;
	return (data->token);
}

t_token	*ft_divide_input(t_data *data)
{
	int	i;
	int	start;

	i = 0;
	while (data->input[i] != '\0')
	{
		printf("en ft_divide_input: data->input[i]: %c\n", data->input[i]);
		while (data->input[i] == ' ')
			i++;
		printf("en ft_divide_input: i: %d\n", i);
		start = i;
		printf("en ft_divide_input: start: %d\n", start);
		// if (data->input[i] == '\"')
		// 	printf("comillas jajant");
		// while (ft_strchr("\"", data->input[i]) == 0)
		// 	i++;
		// else
		// {
		while (data->input[i] != ' ' && data->input[i] != '\0')
			i++;
		printf("en ft_divide_input / despues bucle espacios: i: %d\n", i);
		ft_add_token(&data->token, ft_new_token(data->input, i, start));
		// }
	}
	return (data->token);
}

void	ft_init_parse(t_data *data)
{
	data->token = ft_divide_input(data);
	data->token = ft_assign_type(data);
	if (ft_is_builtin(data->token->str) != 0)
		data->token->type = BUILTIN;
	//ahora deberia ponerme a ejecutar los buitins desde main y adaptar todas la fucniones a token 
	//comprobar lista token
	t_token	*tmp;
	if (data->token)
	tmp = data->token;
	{
		while (data->token)
		{
			printf("en ft_init_parse / token->str: %s\n", data->token->str);
			printf("en ft_init_parse / token->type: %d\n", data->token->type);
			if (data->token->prev != NULL)
				printf("en ft_init_parse / token->prev->str: %s\n", data->token->prev->str);
			data->token = data->token->next;
		}
	}
	data->token = tmp;
}
