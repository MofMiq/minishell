/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:25:39 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/25 13:23:21 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(t_data *data)
{
	char	*nwd;
	char	*owd;

	owd = getcwd(NULL, 0);
	if (chdir(data->args[1]) == 0 && data->argc == 2)
	{
		nwd = getcwd(NULL, 0);
		if (ft_list_cmp(data, "PWD") == 0)
			ft_update_list(data, nwd, "PWD");
		ft_oldpwd(data, owd, nwd);
	}
	else if (data->argc > 2)
	{
		printf("cd: too many args\n");
		return ;
	}
	else
		perror("cd");
}

void	ft_pwd(t_data *data)
{
	char	*cwd;

	if (ft_double_pointer_len(data->args) > 1)
		printf("pwd: too many args\n");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("pwd");
	else
		printf("%s\n", cwd);
}

void	ft_oldpwd(t_data *data, char *owd, char *nwd)
{
	if (ft_strcmp(owd, nwd) != 0)
	{
		if (ft_list_cmp(data, "OLDPWD") == 0)
			ft_update_list(data, owd, "OLDPWD");
	}
}

//El PATH sale como /Users/begarijo.. etc.
//Hay que cambiarlo por MiniShell, para que con estos dos
//solo salga a partir de ahí, pero aún así busque bien.
