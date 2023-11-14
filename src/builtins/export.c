/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:56 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/14 11:41:26 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*This function replicates the 'export' command, which creates or modifies
environmental variables. We first check if the format is correct with 
ft_check_name(). Then, we check if the argument contains an '=' in it or not.
If it contains '=', we add it to 'env.' If it doesn't, we add it to 'exp.'
We have create two separated list for each one.
This is because the 'env' command prints all environmental variables, but
'export' prints only those that have been explicitly marked for export. Next, we
search in the linked list 'env' to check if the variable already exists or not.
If it exists, we modify its value; if not, we create it.*/

void	ft_export(t_data *data)
{
	int		i;

	i = 1;
	while (data->args[i])
	{
		if (ft_check_name(data->args[i], data) == 0)
			i++;
		else
		{
			if (ft_strchr(data->args[i], '='))
			{
				if (data->exp)
					if (ft_list_cmp(data->exp, data->args[i]))
						ft_cmp_and_update(data, data->args[i], 2);
				ft_cmp_and_update(data, data->args[i], 1);
			}
			else
			{
				if (ft_list_cmp(data->exp, data->args[i])
					&& ft_list_cmp(data->env, data->args[i]))
					ft_export_list(&data->exp, data->args[i]);
			}
			i++;
		}
	}
}

/*With this function, we check if the name of the environmental variable we want
to export has the correct grammatical format: the first character can only be a
letter or underscore (_), and the rest of its characters can also be numbers. No
other 'special' characters are allowed.*/

int	ft_check_name(char *name, t_data *data)
{
	int		i;
	char	**split;

	i = -1;
	if ((ft_isalpha_plus(name[0]) == 0))
		return (ft_check_name_print(name, data));
	if (name[0] == '\0')
	{
		data->exit_status = 1;
		return (0);
	}
	else
	{
		split = ft_old_split(name, '=');
		while (split[0][++i] != '\0')
		{
			if (ft_isalnum_plus(split[0][i]) == 0)
			{
				ft_free_double_pointer(split);
				return (ft_check_name_print(name, data));
			}
		}
		ft_free_double_pointer(split);
	}
	return (1);
}

/*This function is used to split the environmental variables at the firs
occurrence of an equal sign (=) into an array. We do this to separate them into
two strings: their name and their value, so we can save them independently in
the env list.*/

char	**ft_alt_split(char *str, char c)
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = NULL;
	if (str)
	{
		if (ft_strchr(str, c))
		{
			while (str[i] != c)
				i++;
			if ((ft_strlen(str) - (i + 1)) != 0)
			{
				matrix = (char **)ft_calloc(3, sizeof(char *));
				matrix[1] = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
			}
			else
				matrix = (char **)ft_calloc(2, sizeof(char *));
			matrix[0] = ft_substr(str, 0, i);
		}
		else
			matrix = ft_no_char_in_split(matrix, str);
		return (matrix);
	}
	return (NULL);
}

char	**ft_no_char_in_split(char **matrix, char *str)
{
	matrix = (char **)malloc(2 * sizeof(char *));
	matrix[0] = ft_strdup(str);
	return (matrix);
}
