/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/12 16:32:46 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		//printf("en ft_divide_input: data->input[i]: %c\n", data->input[i]);
		while (data->input[i] == ' ')
			i++;
		//printf("en ft_divide_input: i: %d\n", i);
		start = i;
		//printf("en ft_divide_input: start: %d\n", start);
		// if (data->input[i] == '\"')
		// 	printf("comillas jajant");
		// while (ft_strchr("\"", data->input[i]) == 0)
		// 	i++;
		// else
		// {
		while (data->input[i] != ' ' && data->input[i] != '\0')
			i++;
		//printf("en ft_divide_input / despues bucle espacios: i: %d\n", i);
		ft_add_token(&data->token, ft_new_token(data->input, i, start));
		// }
		while (data->input[i] == ' ')
			i++;
	}
	return (data->token);
}

void	ft_reconvert_token(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	data->argc = i;
	data->args = (char **)ft_calloc(sizeof(char *), i + 1);
	tmp = data->token;
	i = 0;
	while (tmp)
	{
		data->args[i] = ft_strdup(tmp->str);
		//printf("en ft_reconvert_token: data->args[%d]: %s\n", i, data->args[i]);
		tmp = tmp->next;
		i++;
	}
}

void	ft_init_parse(t_data *data)
{
	data->token = ft_divide_input(data);
	data->token = ft_assign_type(data);
	if (ft_is_builtin(data->token->str) != 0)
		data->token->type = BUILTIN;
	if (ft_is_builtin(data->token->str) == 4
		|| ft_is_builtin(data->token->str) == 1) //AÑADIR CONDICION PARA QUE SE META SOLO SI EXPORT Y $ + =
		data->token = ft_dollar_export(data);
	data->token = ft_parse_dollar(data);
	ft_reconvert_token(data);
}
	//ahora deberia ponerme a ejecutar los buitins desde main y adaptar todas la fucniones a token 
	//comprobar lista token
	// t_token	*tmp;
	// if (data->token)
	// tmp = data->token;
	// {
	// 	while (data->token)
	// 	{
	// 		printf("en ft_init_parse / token->str: %s\n", data->token->str);
	// 		printf("en ft_init_parse / token->type: %d\n", data->token->type);
	// 		data->token = data->token->next;
	// 	}
	// }
	// data->token = tmp;
