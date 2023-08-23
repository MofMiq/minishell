/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/23 18:33:05 by begarijo         ###   ########.fr       */
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
		while (ft_is_space(str[i]) && (ft_is_space(str[i + 1]) || str[i + 1] != '\0'))
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

void	ft_echo(t_data *data)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 1;
	j = 1;
	if (data->args[j] != NULL && data->args[j][0] == '-')
	{
		while (data->args[j][i] == 'n')
		{
			i++;
			flag = 0;
			if (data->args[j][i] != 'n' && data->args[j][i] != '\0')
				flag = 1;
		}
		j++;
	}
	ft_print_echo(data, j);
	if (flag == 1)
		printf("\n");
}
