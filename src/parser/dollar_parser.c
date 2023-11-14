/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:09:16 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/14 11:42:05 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*The functions of this file are essencially for expanding environmental
variables and replacing their name with their definition, such as $USER =
marirodr.
We first check the type of the token because if its singled quoted, we don't
need to expand it. Then we proceed to ft_dollar_aux -42 norm :(-.*/

t_token	*ft_parse_dollar(t_data *data)
{
	t_token	*first;
	int		i;

	first = data->token;
	while (data->token)
	{
		i = 0;
		if (data->token->type != S_QUOTES)
		{
			while (data->token->str[i])
			{
				while (data->token->str[i] && data->token->str[i] != '$')
					i++;
				if (data->token->str[i] && data->token->str[i] == '$'
					&& (data->token->str[i + 1] == ' '
						|| data->token->str[i + 1] == '\0'))
					i++;
				if (data->token->str[i] == '$')
					ft_dollar_aux(data, &data->token, &i);
			}
		}
		data->token = data->token->next;
	}
	data->token = first;
	return (data->token);
}

/*This function is responsible for determining which part of the token is the
environmental variable, starting from the $ sign to a space or another symbol.
After that, we check the variable actually exists in the list where we have
stored them. If it exist, we save its definition in a auxiliaty string (ndef);
if not, we allocate 'empty' memomy to avoid conflicts with the memoryb liberation
funtions later in the code. Finally, we proceed to ft_change_dollar().*/

void	ft_dollar_aux(t_data *data, t_token **token, int *i)
{
	t_elist	*aux;
	int		s;
	char	*cenv;
	char	*ndef;

	s = ++(*i);
	if ((*token)->str[s] == '?')
		ndef = ft_exit_status(data->exit_status, i);
	else
	{
		while ((*token)->str[*i] && !ft_strchr(" $=/-\'\"", (*token)->str[*i]))
			(*i)++;
		cenv = ft_substr((*token)->str, s, (*i) - s);
		if (!ft_list_cmp(data->env, cenv))
		{
			aux = ft_search_node(data->env, cenv);
			ndef = ft_strdup(aux->def);
		}
		else
			ndef = ft_calloc(1, 1);
		free(cenv);
	}
	ft_change_dollar(&data->token, ndef, s - 1, *i);
	(*i) = s - 1;
	free(ndef);
}

/*This function is to check the spacial variable $?, aka the exit status. This
variable exists in bash to determine whether a command was executed successfully
or not and prints its exit code.

We check if its written in the string of the token back in ft_dollar_aux(), and
in case it's true, we replace it with the exit status.*/

char	*ft_exit_status(int exit_status, int *i)
{
	char	*ndef;

	ndef = ft_itoa(exit_status);
	(*i)++;
	return (ndef);
}

/*In this function, we copy the definition "manually", which means that before
the $ sign, we copy from the string of the token. When our counter is equal to
'drop', we start copying from the environmental variable definition until its
end, and finally we resume copying into the string from where we should in the
token string. This way we completelly replace the environmental variable one by
one.

To be more clear, lets make an example:
If our input is like: Minishell> echo "hello $USER world"
We are going proceed like this:
	1 - We copy 'hello ' from token string.
	2 - Then, we copy 'marirodr' from environmental variable (nstr).
	3 - Finally, we resume copying from token string from ' world'.

That way, we replace "hello $USER world" to "hello marirodr world".
*/

void	ft_change_dollar(t_token **token, char *nstr, int drop, int take)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char) * (ft_strlen((*token)->str)) \
	- (take - drop) + ft_strlen(nstr));
	if (!copy)
		return ;
	while (i < drop)
		copy[i++] = (*token)->str[j++];
	j = 0;
	while (nstr[j])
		copy[i++] = nstr[j++];
	j = take;
	while ((*token)->str[j])
		copy[i++] = (*token)->str[j++];
	copy[i] = '\0';
	free((*token)->str);
	(*token)->str = ft_strdup(copy);
	free(copy);
}

/*This function is used to check if the input written by the user
only have spaces, so we stop the execution of more things.*/

int	ft_is_all_space(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	data->exit_status = 127;
	return (1);
}
