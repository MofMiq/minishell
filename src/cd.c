/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:25:39 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/23 16:15:09 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(t_data *data)
{
	char	*nwd;

	if (chdir(data->args[1]) == 0 && data->argc == 2)
	{
		nwd = getcwd(NULL, 0);
		data->env = ft_list_cmp(data, "PWD");
		if (data->env != NULL)
		{
			free(data->env->def);
			data->env->def = ft_strdup(nwd);
		}
	}
	if (data->argc > 2)
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

//El PATH sale como /Users/begarijo.. etc.
//Hay que cambiarlo por MiniShell, para que con estos dos
//solo salga a partir de ahí, pero aún así busque bien.
