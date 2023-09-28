/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/27 11:02:08 by marirodr         ###   ########.fr       */
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
		if (data->token->str[0] == '\''
			|| (data->token->str[0] != '\''
				&& ft_strchr(data->token->str, '\'')))
			data->token->type = S_QUOTES;
		else if (data->token->str[0] == '\"'
			|| (data->token->str[0] != '\"'
				&& ft_strchr(data->token->str, '\"')))
			data->token->type = D_QUOTES;
		else if (data->token->str[0] == '|')
			data->token->type = PIPE;
		else if (data->token->str[0] == '>' && data->token->str[1] == '>')
			data->token->type = D_GREAT;
		else if (data->token->str[0] == '>')
			data->token->type = GREAT;
		else if (data->token->str[0] == '<' && data->token->str[1] == '<')
			data->token->type = D_LESS;
		else if (data->token->str[0] == '<')
			data->token->type = LESS;
		else
			data->token->type = NO_QUOTES;
		data->token = data->token->next;
	}
	data->token = tmp;
	return (data->token);
}

void	ft_subdivide_input(t_data *data, int *i, int *start)
{
	while (!(ft_strchr(" '\"''\''|", data->input[*i])) && data->input[*i] != '\0')
		(*i)++;
	if (data->input[*i] == '\'' || data->input[*i] == '\"')
	{
		while (!(ft_strchr("'\"''\''", data->input[++(*i)])))
			continue ;
		(*i)++;
	}
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
		if (ft_strchr("'\"''\''", data->input[i]))
			ft_quotes(data, &i, &start, data->input[i]);
		else if (data->input[i] == '|' && data->input[i + 1] == '|')
			break ;
		else if (ft_strchr("|<>", data->input[i]))
			ft_redirections(data, &i, &start, data->input[i]);
		else
			ft_subdivide_input(data, &i, &start);
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
		if (tmp->type >= 1 && tmp->type <= 4)
			i++;
		tmp = tmp->next;
	}
	data->argc = i;
	data->args = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!data->args)
		return ;
	tmp = data->token;
	i = 0;
	while (tmp)
	{
		if (tmp->type >= 1 && tmp->type <= 4)
			data->args[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
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
			ft_putstr_fd("en ft_init_parse / token->str: ", data->fdout);
			ft_putstr_fd(data->token->str, data->fdout);
			ft_putchar_fd('\n', data->fdout);
			ft_putstr_fd("en ft_init_parse / token->type: ", data->fdout);
			ft_putnbr_fd(data->token->type, data->fdout);
			ft_putchar_fd('\n', data->fdout);
			data->token = data->token->next;
		}
	}
	data->token = tmp;
	ft_reconvert_token(data);
}
	//comprobar lista token
