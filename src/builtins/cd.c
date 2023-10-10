/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:25:39 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/09 18:33:37 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_change_dir(t_data *data, char *owd)
{
	char	*nwd;

	nwd = getcwd(NULL, 0);
	if (ft_list_cmp(data->env, "PWD") == 0)
		ft_update_list(data->env, nwd, "PWD");
	ft_oldpwd(data, owd, nwd);
	free(nwd);
}

void	ft_cd(t_data *data)
{
	char	*owd;
	t_elist	*home;

	owd = getcwd(NULL, 0);
	if (chdir(data->args[1]) == 0 && data->argc >= 2)
		ft_change_dir(data, owd);
	else if (data->argc == 1)
	{
		if (ft_list_cmp(data->env, "HOME") == 0)
		{
			home = ft_search_node(data->env, "HOME");
			chdir(home->def);
			ft_change_dir(data, owd);
		}
		else
			ft_putstr_fd("bash: cd: HOME not set\n", data->fdout);
	}
	else
		perror("cd");
	free(owd);
}

void	ft_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("pwd");
	else
	{
		ft_putstr_fd(cwd, data->fdout);
		ft_putchar_fd('\n', data->fdout);
	}
	free(cwd);
}

void	ft_oldpwd(t_data *data, char *owd, char *nwd)
{
	char	*join;

	join = NULL;
	if (ft_strcmp(owd, nwd) != 0)
	{
		join = ft_strjoin("OLDPWD=", owd);
		ft_cmp_and_update(data, join, 1);
		free(join);
	}
}

/*le he puesto una boleana ha esta funcion para adaptarla a las dos
listas: 1 es para cuando realmente necesitamos hacer actualizar una
lista (la funcion origina de la funcion); 2 es para cuando necesitamos
borrar de la lista de export. he tenido que hacerlos asi porque tuve
problemas intentando reutilizar el unset para esto (creo que con los
parametros que le pasamos y tal). */

void	ft_cmp_and_update(t_data *data, char *var_env, int i)
{
	char	**splitted;
	t_elist	*tmp;

	if (i == 1)
	{
		splitted = ft_old_split(var_env, '='); //por que usar aqui el split y no el mini_split, por las pruebas con env y export me viene mejor el mini_split, no se si se joderia mucho el OLDPWD con el mini_split?? // nuevo conflico entre tres versiones de split diferentes xddddd
		if (ft_list_cmp(data->env, splitted[0]) == 0)
			ft_update_list(data->env, splitted[1], splitted[0]);
		else if (ft_list_cmp(data->env, splitted[0]) != 0)
			ft_add_back(&data->env, ft_new_node(splitted));
		ft_free_double_pointer(splitted);
	}
	else if (i == 2)
	{
		tmp = data->exp;
		splitted = ft_mini_split(var_env, '=');
		ft_remove_if(tmp, splitted[0], &data->exp);
		ft_free_double_pointer(splitted);
	}
}

//El PATH sale como /Users/begarijo.. etc.
//Hay que cambiarlo por MiniShell, para que con estos dos
//solo salga a partir de ahí, pero aún así busque bien.
