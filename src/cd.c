/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:25:39 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/29 10:38:39 by begarijo         ###   ########.fr       */
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
		if (ft_list_cmp(data->env, "PWD") == 0)
			ft_update_list(data->env, nwd, "PWD");
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
	char	**old;

	old = ft_split(ft_strjoin("OLDPWD=", owd), '=');
	if (ft_strcmp(owd, nwd) != 0)
	{
		if (ft_list_cmp(data->env, "OLDPWD") == 0)
			ft_update_list(data->env, owd, "OLDPWD");
		else if (ft_list_cmp(data->env, "OLDPWD") != 0)
			ft_add_back(&data->env, ft_new_node(old));
	}
	ft_free_double_pointer(old);
}

//El PATH sale como /Users/begarijo.. etc.
//Hay que cambiarlo por MiniShell, para que con estos dos
//solo salga a partir de ahí, pero aún así busque bien.
