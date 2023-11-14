/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:49:30 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/14 11:42:11 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* As ft_quotes(), this function is a part of ft_divide_input(), but for the
parts we consider as redirection, that is the simbol (><) and the following
text (file's name); or the pipe (|), which is saved separately.*/

void	ft_sub_red(t_data *data, int *i, int *start, char c)
{
	if (c == '|' && data->input[(*i) + 1] != c)
		(*i)++;
	else if (c == '<' || c == '>')
	{
		while (data->input[*i] == c)
			(*i)++;
		while (data->input[*i] == ' ' && data->input[*i])
			(*i)++;
		while (data->input[*i] != ' ' && data->input[*i])
			(*i)++;
	}
	ft_add_token(&data->token, ft_new_token(data->input, *i, *start, data));
}

/*This function is used to check syntax error for pipes and redirections,
for example, if there're more than two consecutive > symbols ('>>>') or if
there are two sybols(|><) in a row but separated by spaces ('|  |').*/

int	ft_bad_redi(t_token *token, int fd, t_data *data)
{
	t_token	*aux;
	t_token	*last;

	aux = token;
	last = ft_last_token(token);
	while (aux)
	{
		if (aux->type == PIPE && (aux->next && aux->next->type >= PIPE
				&& aux->next->type <= HERE_DOC))
		{
			ft_putstr_fd("syntax error near unexpected token\n", fd);
			data->exit_status = 1;
			return (1);
		}
		if ((aux->type == APPEND && ft_strncmp(aux->str, ">>>", 3) == 0)
			|| (aux->type == HERE_DOC && ft_strncmp(aux->str, "<<<", 3) == 0)
			|| (ft_bad_syntax(aux) && (aux->type >= 6 && aux->type <= 9)))
		{
			ft_putstr_fd("syntax error near unexpected token\n", fd);
			data->exit_status = 1;
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}

/* This funtion, like ft_bad_redi(), is used to check syntax error for pipes
and redirections, particularly in cases like '>   >'. That was a problem for us
due to how we separated redirections tokens -see ft_sub_red()-.*/

int	ft_bad_syntax(t_token *aux)
{
	int	i;

	if (aux->type == OUT || aux->type == IN)
		i = 1;
	if (aux->type == APPEND || aux->type == HERE_DOC)
		i = 2;
	while (aux->str[i])
	{
		if (aux->str[i] == '>' || aux->str[i] == '<' || aux->str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

/*This function is to add an space between a redirection symbol (><) and
the following text -the name of the file-. (ej: echo hello >file)*/

void	ft_add_space(t_data *data)
{
	t_token	*tmp;
	int		i;
	char	*space;

	tmp = data->token;
	while (data->token)
	{
		if (data->token->type >= OUT && data->token->type <= HERE_DOC)
		{
			if (!ft_strchr(data->token->str, ' '))
			{
				i = -1;
				space = (char *)ft_calloc(ft_strlen(data->token->str) + 1, 1);
				while (ft_strchr("<>", data->token->str[++i]))
					space[i] = data->token->str[i];
				space[i] = ' ';
				while (space[i++])
					space[i] = data->token->str[i - 1];
				free(data->token->str);
				data->token->str = space;
			}
		}
		data->token = data->token->next;
	}
	data->token = tmp;
}
