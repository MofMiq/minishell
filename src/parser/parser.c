/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/20 16:58:39 by marirodr         ###   ########.fr       */
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
		else if (data->token->str[0] != '\'' && ft_strchr(data->token->str, '\'')) //cambiar esto
			data->token->type = S_QUOTES;
		else if (data->token->str[0] == '\"')
			data->token->type = D_QUOTES;
		else if (data->token->str[0] != '\"' && ft_strchr(data->token->str, '\"'))  //cambiar esto
			data->token->type = D_QUOTES;
		else
			data->token->type = NO_QUOTES;
		data->token = data->token->next;
	}
	data->token = tmp;
	return (data->token);
}

int	ft_is_closed(char *str, char c)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == c)
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
		while (data->input[i] == ' ')
			i++;
		start = i;
		if (data->input[i] == '\"' || data->input[i] == '\'')
			ft_quotes(data, &i, &start, data->input[i]);
		else
		{
			while ((ft_strchr(" '\"''\''", data->input[i]) == NULL) && data->input[i] != '\0')
				i++;
			if (data->input[i] == '\'' || data->input[i] == '\"')
			{
				while ((ft_strchr("'\"''\''", data->input[++i]) == NULL))
					continue ;
				i++;
			}
			ft_add_token(&data->token, ft_new_token(data->input, i, start));
		}
		while (data->input[i] == ' ' && data->input[i] != '\0')
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

int		ft_count_qoutes(char *str)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			c++;
		i++;
	}
	return (c);
}

void	ft_ignore_quotes(t_data *data)
{
	t_token	*tmp;
	char	*copy;
	int		i;
	int		j;
	int		len;

	tmp = data->token;
	while (data->token)
	{
		if (data->token->type == S_QUOTES || data->token->type == D_QUOTES)
		{
			i = 0;
			j = 0;
			len = (ft_strlen(data->token->str) - ft_count_qoutes(data->token->str));
			copy = ft_calloc(len + 1, sizeof(char));
			while (data->token->str[i])
			{
				if ((ft_strchr("'\"''\''", (data->token->str[i])) == NULL))
					copy[j++] = data->token->str[i++];
				else
					i++;
			}
			free(data->token->str);
			data->token->str = NULL;
			data->token->str = ft_strdup(copy);
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
