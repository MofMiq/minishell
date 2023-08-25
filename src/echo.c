/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/24 18:26:01 by begarijo         ###   ########.fr       */
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
	int	k;

	i = 1;
	flag = 0;
	j = 1;
	k = 1;
	if (data->args[j] != NULL && data->args[j][0] == '-')
	{
		while (data->args[j][i] == 'n' && data->args[j][0] == '-')
		{
			i++;
			flag = 1;
			if (data->args[j][i] != 'n' && data->args[j][i] != '\0')
				flag = 0;
		}
		if (flag == 1)
			k += 1;
		j++;
		i = 1;
	}
	ft_print_echo(data, k);
	if (flag == 0)
		printf("\n");
}

