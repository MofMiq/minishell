/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:25:39 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/23 12:07:51 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(t_data *data)
{
	char	*cwd;
	char	*nwd;

	if (ft_double_pointer_len(data->args) > 2)
		printf("Muchos argumentos\n");
	cwd = getcwd(NULL, 0);
	printf("\nPrimero estas aquí: %s\n", cwd);
	chdir(data->args[1]);
	nwd = getcwd(NULL, 0);
	printf("\nSe supone que te mueves aquí??: %s\n", nwd);
}

void	ft_pwd(t_data *data)
{
	char	*cwd;

	if (ft_double_pointer_len(data->args) > 1)
		printf("Muchos args\n");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("pwd");
	else
		printf("%s\n", cwd);
}

//El PATH sale como /Users/begarijo.. etc.
//Hay que cambiarlo por MiniShell, para que con estos dos
//solo salga a partir de ahí, pero aún así busque bien.
