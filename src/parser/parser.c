/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/18 17:52:48 by marirodr         ###   ########.fr       */
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

int	ft_is_closed(char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			q++;
		i++;
	}
	//printf("%sen ft_is_closed: %d%s\n", PINK, q, END);
	return (q);
}

void	ft_quotes(t_data *data, int *i, int *start, char q)
{
	//printf("en ft_quotes: antes data->input[start]: %c\n", data->input[*start]);
	//printf("en ft_quotes: antes data->input[i]: %c\n", data->input[*i]);
	if (data->input[*i] == q)
		(*i)++;
	//printf("en ft_quotes: antes bucle data->input[start]: %c\n", data->input[*start]);
	//printf("en ft_quotes: antes bucle data->input[i]: %c\n", data->input[*i]);
	while (data->input[*i] != q)
		(*i)++;
	if (data->input[*i] == q && (data->input[(*i) + 1] == ' ' || data->input[(*i) + 1] == '\0')) //pa reservar una espacio mas de memoria para las "" y \0
		(*i)++;
	//printf("en ft_quotes: despues data->input[start]: %c\n", data->input[*start]);
	//printf("en ft_quotes: despues data->input[i]: %c\n", data->input[*i]);
	ft_add_token(&data->token, ft_new_token(data->input, *i, *start));
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
		if (data->input[i] == '\"' || data->input[i] == '\'')
			ft_quotes(data, &i, &start, data->input[i]);
		// while (ft_strchr("\"", data->input[i]) == 0)
		// 	i++;
		else
		{
			while (data->input[i] != ' ' && data->input[i] != '\0')
				i++;
		//	printf("en ft_divide_input / antes add_token: i: %d\n", i);
			ft_add_token(&data->token, ft_new_token(data->input, i, start));
		}
		while (data->input[i] == ' ' && data->input[i] != '\0')
			i++;
		//printf("en ft_divide_input / despues espacio: i: %d\n", i);
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
	if (!data->args)
		printf("jaja no kapasao\n");
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

void	ft_ignore_quotes(t_data *data)
{
	t_token	*tmp;
	char	*copy;
	char	*q;

	tmp = data->token;
	while (data->token)
	{
		if (data->token->type == S_QUOTES || data->token->type == D_QUOTES)
		{
			//printf("en ft_ignore data->token->str[0]: %i\n", data->token->str[0]);
			q = ft_strchr("\'\"", data->token->str[0]);
			//printf("en ft_ignore q: %s\n", q);
			copy = ft_strtrim(data->token->str, q);
			//printf("en ft_ignore copy: %s\n", copy);
			free(data->token->str);
			data->token->str = NULL;
			data->token->str = ft_strdup(copy);
			//printf("en ft_ignore data->token->str: %s\n", data->token->str);
			free(copy);
		}
		data->token = data->token->next;
	}
	data->token = tmp;
}

void	ft_init_parse(t_data *data)
{
	data->token = ft_divide_input(data);
	data->token = ft_assign_type(data);
	ft_ignore_quotes(data);
	if (ft_is_builtin(data->token->str) != 0)
		data->token->type = BUILTIN;
	// if (ft_is_builtin(data->token->str) == 4 //creo que esta condicion sobra en verdad, probar mas y mejor luego con el resto de builtins
	// 	|| ft_is_builtin(data->token->str) == 1)
	data->token = ft_dollar_export(data);
	data->token = ft_parse_dollar(data);
	t_token	*tmp;
	if (data->token)
	tmp = data->token;
	{
		while (data->token)
		{
			printf("en ft_init_parse / token->str: %s\n", data->token->str);
			printf("en ft_init_parse / token->type: %d\n", data->token->type);
			data->token = data->token->next;
		}
	}
	data->token = tmp;
	ft_reconvert_token(data);
}
	//comprobar lista token
