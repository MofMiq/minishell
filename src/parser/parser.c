/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:17:49 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/14 11:42:07 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*This is like a  handling funcion in charge of one of the essential parts of
this project: parsing. Which is in charge of transforming an in input to make
it suitable for processing.

This entire process is divided into:
	1. Divide the input into a linked list of tokens.
	2. Assign each tokens its type, defined in the library as macros.
	3. Remove quotes from the tokens once we know what they represent.
	4. Check for our built-in commands.
	5. Add spaces in the redirections tokens in case the symbols (><) and the
		text aren't separated by spaces for proper processing.
	6. Combine the string of tokens that weren't separated by spaces in the
		original input.
	7. Recently added a new function to expand - and ~ symbols for 'cd' built-in
*/

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
	ft_change_symbols(data);
}

/* ft_divide_input and ft_subdivide_input work as a single fucntion but they're 
divided into two functions due to the 42 norm. Essentially, both read the
original input and search for spaces or symbols ("'><|) to determine a start
and an end, and then save that part of the input in a token of a linked list.

To be more clear, let's make an example:
If our input is like: Minishell> echo "hello world" > file | wc
We are going to create five tokens:
	1. echo
	2. "hello world"
	3. > file
	4. |
	5. wc

Later, this will be useful to know how we should process them.*/

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

/*This fucntion is used to examine the strings saved in the tokens in order to
determine the type of text we have. As we have considered, there're 9 different
types of tokens:
	- Single quotes: ''
	- Double quotes: ""
	- Pipe: |
	- Out redirection: >
	- Append redirention: >>
	- In redirection: <
	- Here_doc redirection : <<
	- No quotes for the rest.
	- The assignment of built-ins is done later in the code.
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

/*This fucntion is to expand - and ~symbols for the 'cd' built-in.*/

void	ft_change_symbols(t_data *data)
{
	t_elist	*tmp;

	if (data->token->next && ft_strcmp(data->token->str, "cd") == 0)
	{
		if (ft_strcmp(data->token->next->str, "-") == 0)
		{
			if (ft_list_cmp(data->env, "OLDPWD") == 0)
			{
				tmp = ft_search_node(data->env, "OLDPWD");
				free(data->token->next->str);
				data->token->next->str = ft_strdup(tmp->def);
			}
		}
		if (ft_strcmp(data->token->next->str, "~") == 0)
		{
			if (ft_list_cmp(data->env, "HOME") == 0)
			{
				tmp = ft_search_node(data->env, "HOME");
				free(data->token->next->str);
				data->token->next->str = ft_strdup(tmp->def);
			}
		}
	}
}
