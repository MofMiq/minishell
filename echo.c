/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:54:01 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/21 17:14:49 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
		while (ft_is_space(str[i]) && ft_is_space(str[i + 1]) && str[i + 1] != '\0')
			i++;
		if (ft_is_space(str[i]) && str[i + 1] != '\0')
			write(1, " ", 1);
	}
}

void	ft_is_last_arg(char **argv, int pos)
{
	int	i;

	i = 0;
	while (argv[pos + i] != NULL)
	{
		epur_str(argv[pos + i]);
		if (argv[pos + i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (argc == 3 && strcmp(argv[2], "-n") == 0)
		printf("pocos args");
	else if (argc == 3 && strcmp(argv[2], "-n") != 0)
		epur_str(argv[2]);
	else if (argc > 3 && strcmp(argv[2], "-n") == 0)
		ft_is_last_arg(argv, 3);
	else if (argc > 3 && strcmp(argv[2], "-n") != 0)
	{
		ft_is_last_arg(argv, 2);
		flag = 1;
	}
	if (flag == 1)
		printf("\n");
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc >= 3 && strcmp(argv[1], "echo") == 0)
		ft_echo(argc, argv);
	else if (argc < 3)
		printf("Errorsito");
	return (0);
}
*/
