/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/18 19:13:42 by marirodr         ###   ########.fr       */
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
			data->token->type = APPEND;
		else if (data->token->str[0] == '>')
			data->token->type = OUT;
		else if (data->token->str[0] == '<' && data->token->str[1] == '<')
			data->token->type = HERE_DOC;
		else if (data->token->str[0] == '<')
			data->token->type = IN;
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
	while (!(ft_strchr(" |'\"''\''<>", data->input[*i])) && data->input[*i] != '\0')
		(*i)++;
	ft_add_token(&data->token, ft_new_token(data->input, *i, *start));
}
		// if (data->input[i] && ft_strchr("'\"''\''", data->input[i]))
		// 	i++;

t_token	*ft_divide_input(t_data *data) //puedo arrejuntar ft_subdivide_input???
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

void	ft_reconvert_token(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->curr_tkn;
	i = 0;
	while (tmp)
	{
		if (tmp->type >= PIPE && tmp->type <= HERE_DOC)
			break ;
		else
		{
			i++;
			tmp = tmp->next;
		}
	}
	data->argc = i;
	data->args = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!data->args)
		return ;
	tmp = data->curr_tkn;
	i = 0;
	while (tmp)
	{
		if (tmp->type >= PIPE && tmp->type <= HERE_DOC)
			break ;
		data->args[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
}

void	ft_remove_if_token(t_token *curr, char *cstr, t_token **token)
{
	while (curr)
	{
		if (ft_strcmp(curr->str, cstr) == 0)
		{
			if (curr->prev == NULL)
			{
				*token = curr->next;
				if (*token)
					(*token)->prev = NULL;
			}
			else
			{
				curr->prev->next = curr->next;
				if (curr->next)
				{
					curr->next->prev = curr->prev;
				}
			}
			free(curr->str);
			free(curr);
		}
		curr = curr->next;
	}
}

t_token	*ft_join_quotes(t_data *data)
{
	t_token	*tmp;
	t_token	*curr;

	if (data->token->next != NULL)
	{
		tmp = data->token;
		data->token = data->token->next;
		while (data->token)
		{
			if ((data->token->type >= BUILTIN && data->token->type <= D_QUOTES) && data->token->space == 0) //no_quotes y builtins tambien en realidad tambien
			{
				printf("----vamos al lio----ft_join_quotes: data->token->str: %s\n", data->token->str);
				data->token->prev->str = ft_strjoin_gnl(data->token->prev->str, data->token->str);
				// if (data->token->prev->type && data->token->prev->type != NO_QUOTES) //esto no porque no respetaria el typo del primero
				// 	data->token->prev->type = NO_QUOTES;
				curr = data->token;
				printf("ft_join_quotes: curr->str: %s\n", curr->str);
				ft_remove_if_token(curr, curr->str, &data->token);
			}	
			data->token = data->token->next;
		}
		data->token = tmp;
	}
	return (data->token);
}
	//char *join_str;
	// free(data->token->prev->str);
	// data->token->prev->str = ft_strdup(join_str);
	// free(join_str);
	// tmp = data->token;
	// if (data->token->next == NULL)
	// 	return (data->token);
	// else
	// 	data->token = data->token->next;
	// while (data->token)
	// {
	// 	if ((data->token->type >= BUILTIN && data->token->type <= D_QUOTES) && data->token->space == 0) //no_quotes y builtins tambien en realidad tambien
	// 	{
	// 		printf("----vamos al lio----ft_join_quotes: data->token->str: %s\n", data->token->str);
	// 		data->token->prev->str = ft_strjoin_gnl(data->token->prev->str, data->token->str);
	// 		if (data->token->prev->type && data->token->prev->type != NO_QUOTES)
	// 			data->token->prev->type = NO_QUOTES;
	// 		curr = data->token;
	// 		printf("ft_join_quotes: curr->str: %s\n", curr->str);
	// 		// free(data->token->prev->str);
	// 		// data->token->prev->str = ft_strdup(join_str);
	// 		// free(join_str);
	// 		ft_remove_if_token(curr, curr->str, &data->token);
	// 	}	
	// 	data->token = data->token->next;
	// }
	// data->token = tmp;
	// return (data->token);

//tener en cuenta los camos type y space

void	ft_init_parse(t_data *data)
{
	data->token = ft_divide_input(data);
	data->token = ft_assign_type(data);
	ft_ignore_quotes(data);
	if (ft_is_builtin(data->token->str) != 0)
		data->token->type = BUILTIN;
	data->token = ft_parse_dollar(data);
	ft_add_space(data);
	t_token	*tmp;
	if (data->token)
	tmp = data->token;
	{
		while (data->token)
		{
			printf("%sen ft_init_parse antes join / token->str: %s\n", BLUE, data->token->str);
			printf("en ft_init_parse antes join / token->type: %d / token->space: %d%s\n", data->token->type, data->token->space, END);
			data->token = data->token->next;
		}
	}
	data->token = tmp;
	data->token = ft_join_quotes(data);
	if (data->token)
	tmp = data->token;
	{
		while (data->token)
		{
			printf("%sen ft_init_parse RESULTADO / token->str: %s\n", PINK, data->token->str);
			printf("en ft_init_parse RESULTADO / token->type: %d / token->space: %d%s\n", data->token->type, data->token->space, END);
			data->token = data->token->next;
		}
	}
	data->token = tmp;
}
	//comprobar lista token
	// ft_putstr_fd("en ft_init_parse / data->input: ", data->fdout);
	// ft_putstr_fd(data->input, data->fdout);
	// ft_putchar_fd('\n', data->fdout);

			// ft_putstr_fd(PINK, data->fdout);
			// ft_putstr_fd("en ft_init_parse / token->str: ", data->fdout);
			// ft_putstr_fd(data->token->str, data->fdout);
			// ft_putchar_fd('\n', data->fdout);
			// ft_putstr_fd("en ft_init_parse / token->type: ", data->fdout);
			// ft_putnbr_fd(data->token->type, data->fdout);
			// ft_putchar_fd('\n', data->fdout);
			// ft_putnbr_fd(data->token->space, data->fdout);
			// ft_putchar_fd('\n', data->fdout);
			// ft_putstr_fd(END, data->fdout);