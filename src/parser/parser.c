/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/04 18:26:17 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
no me acuerdo exactamente por qué motivo puse esta condicion para amabs comillas
asi pero ahora me esta dando problemas en otro sitios, asi que voy a cambiar la
codicion pero la dejo aqui por si acaso en un futuro la lio y esto me da una
pista
if (data->token->str[0] == '\'' || (data->token->str[0] != '\'' &&
ft_strchr(data->token->str, '\'')))
*/

t_token	*ft_assign_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (data->token)
	{
		if (data->token->str[0] == '\''
			&& data->token->str[ft_strlen(data->token->str) - 1] == '\'') //probar guay esta mierda
			data->token->type = S_QUOTES;
		else if (data->token->str[0] == '\"'
			&& data->token->str[ft_strlen(data->token->str) - 1] == '\"')
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
	// if (data->input[*i] == '\'' || data->input[*i] == '\"')
	// {
	// 	while (!(ft_strchr("'\"''\''", data->input[++(*i)])))
	// 		continue ;
	// 	(*i)++;
	// }

void	ft_subdivide_input(t_data *data, int *i, int *start)
{
	while (!(ft_strchr(" |'\"''\''", data->input[*i])) && data->input[*i] != '\0')
		(*i)++;
	ft_add_token(&data->token, ft_new_token(data->input, *i, *start));
}
		// if (data->input[i] && ft_strchr("'\"''\''", data->input[i]))
		// 	i++;

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
			ft_redirections(data, &i, &start, data->input[i]);
		else
			ft_subdivide_input(data, &i, &start);
		while (data->input[i] && data->input[i] == ' ')
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
		//if (tmp->type >= 1 && tmp->type <= 4)
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
		//if (tmp->type >= 1 && tmp->type <= 4)
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
			ft_putstr_fd(PINK, data->fdout);
			ft_putstr_fd("en ft_init_parse / token->str: ", data->fdout);
			ft_putstr_fd(data->token->str, data->fdout);
			ft_putchar_fd('\n', data->fdout);
			ft_putstr_fd("en ft_init_parse / token->type: ", data->fdout);
			ft_putnbr_fd(data->token->type, data->fdout);
			ft_putchar_fd('\n', data->fdout);
			ft_putnbr_fd(data->token->space, data->fdout);
			ft_putchar_fd('\n', data->fdout);
			ft_putstr_fd(END, data->fdout);
			data->token = data->token->next;
		}
	}
	data->token = tmp;
	ft_reconvert_token(data);
	int i = 0;
	while(data->args[i])
	{
		printf("%sen ft_init_parsedata->args[%i]: %s%s\n", BLUE, i, data->args[i], END);
		i++;
	}
}
	//comprobar lista token
	// ft_putstr_fd("en ft_init_parse / data->input: ", data->fdout);
	// ft_putstr_fd(data->input, data->fdout);
	// ft_putchar_fd('\n', data->fdout);
