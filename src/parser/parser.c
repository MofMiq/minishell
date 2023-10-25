/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/24 16:45:14 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_parse(t_data *data)
{
	data->token = ft_divide_input(data);
	ft_assign_type(data);
	ft_ignore_quotes(data);
	if (ft_is_builtin(data->token->str) != 0)
		data->token->type = BUILTIN;
	data->token = ft_parse_dollar(data);
	ft_add_space(data);
	if (data->token->next != NULL)
		ft_join_glued_tokes(data);
}

	//debug
	// t_token *tmp;
	// if (data->token)
	// tmp = data->token;
	// {
	// 	while (data->token)
	// 	{
//printf("%sen ft_init_parse token->str: %s\n", PINK, data->token->str);
	//printf("en ft_init_parse token->type: %d / token->space: %d%s\n",
	//data->token->type, data->token->space, END);
	// 		data->token = data->token->next;
	// 	}
	// }
	// data->token = tmp;

t_token	*ft_divide_input(t_data *data)
{
	int	i;
	int	start;

	i = 0;
	while (data->input[i] != '\0')
	{
		while (data->input[i] && data->input[i] == ' ')
			i++;
		start = i;
		if (data->input[i] && ft_strchr("'\"''\''", data->input[i]))
			ft_quotes(data, &i, &start, data->input[i]);
		else if (data->input[i] && data->input[i] == '|'
			&& data->input[i + 1] == '|')
			break ;
		else if (data->input[i] && ft_strchr("|<>", data->input[i]))
			ft_sub_red(data, &i, &start, data->input[i]);
		else
			ft_subdivide_input(data, &i, &start);
		while (data->input[i] && data->input[i] == ' ')
			i++;
	}
	return (data->token);
}

void	ft_subdivide_input(t_data *data, int *i, int *start)
{
	while (!(ft_strchr(" |'\"''\''<>", data->input[*i]))
		&& data->input[*i] != '\0')
		(*i)++;
	ft_add_token(&data->token, ft_new_token(data->input, *i, *start, data));
}

/*
no me acuerdo exactamente por qué motivo puse esta condicion para amabs comillas
asi pero ahora me esta dando problemas en otro sitios, asi que voy a cambiar la
codicion pero la dejo aqui por si acaso en un futuro la lio y esto me da una
pista
if (data->token->str[0] == '\'' || (data->token->str[0] != '\'' &&
ft_strchr(data->token->str, '\'')))
*/
void	ft_assign_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->str[0] == '\'' && tmp->str[ft_strlen(tmp->str) - 1] == '\'')
			tmp->type = S_QUOTES;
		else if (tmp->str[0] == '\"'
			&& tmp->str[ft_strlen(tmp->str) - 1] == '\"')
			tmp->type = D_QUOTES;
		else if (tmp->str[0] == '|')
			tmp->type = PIPE;
		else if (tmp->str[0] == '>' && tmp->str[1] == '>')
			tmp->type = APPEND;
		else if (tmp->str[0] == '>')
			tmp->type = OUT;
		else if (tmp->str[0] == '<' && tmp->str[1] == '<')
			tmp->type = HERE_DOC;
		else if (tmp->str[0] == '<')
			tmp->type = IN;
		else
			tmp->type = NO_QUOTES;
		tmp = tmp->next;
	}
	tmp = data->token;
}
