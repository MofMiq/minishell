/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/29 10:16:39 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//En principio todo ok

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	epur_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (ft_is_space(str[i]))
			i++;
		while (!ft_is_space(str[i]) && str[i] != '\0')
		{
			write(1, &str[i], 1);
			i++;
		}
		while (ft_is_space(str[i]) && (ft_is_space(str[i + 1])
				|| str[i + 1] != '\0'))
			i++;
		if (ft_is_space(str[i]) && str[i + 1] != '\0')
			write(1, " ", 1);
	}
}

void	ft_print_echo(t_data *data, int pos)
{
	int	i;

	i = 0;
	while (data->args[pos + i] != NULL)
	{
		epur_str(data->args[pos + i]);
		if (data->args[pos + i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

/*Arreglar echo, si hago echo -n -nk hola, no me coge el 2º arg
* A lo mejor algo con data->argc??? s*/

int	ft_is_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[0] == '-')
	{
		while (str[i] == 'n' && str[i] != '\0')
		{
			i++;
			if (str[i - 1] == 'n' && str[i] == '\0')
				return (1);
		}
		return (0);
	}
	return (0);
}

void	ft_echo(t_data *data)
{
	int	flag;
	int	j;
	int	p;

	flag = 0;
	j = 1;
	p = j;
	while (ft_is_flag(data->args[1]))
	{
		flag = 1;
		if (ft_is_flag(data->args[j]) && ft_is_flag(data->args[j + 1]))
			p = j++;
		else if (ft_is_flag(data->args[j]) && !ft_is_flag(data->args[j + 1]))
		{
			p = j + 1;
			break ;
		}
	}
	ft_print_echo(data, p);
	if (flag == 0)
		printf("\n");
}
