/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:25:39 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/06 10:12:05 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	owd = getcwd(NULL, 0);
	if (chdir(data->args[1]) == 0 && data->argc >= 2)
		ft_change_dir(data, owd);
	else
		perror("cd");
	free(owd);
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("pwd");
	else
		printf("%s\n", cwd);
	free(cwd);
}

void	ft_oldpwd(t_data *data, char *owd, char *nwd)
{
	//char	**old;
	char	*join;

	//old = NULL;
	join = NULL;
	if (ft_strcmp(owd, nwd) != 0)
	{
		join = ft_strjoin("OLDPWD=", owd);
		ft_cmp_and_update(data, join, 1);
		// old = ft_split(join, '=');
		// if (ft_list_cmp(data->env, "OLDPWD") == 0)
		// 	ft_update_list(data->env, owd, "OLDPWD");
		// else if (ft_list_cmp(data->env, "OLDPWD") != 0)
		// 	ft_add_back(&data->env, ft_new_node(old));
		free(join);
	}
	//ft_free_double_pointer(old);
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
		splitted = ft_split(var_env, '='); //por que usar aqui el split y no el mini_split, por las pruebas con env y export me viene mejor el mini_split, no se si se joderia mucho el OLDPWD con el mini_split??
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
		printf("en ft_cmp_and_update: splted[0]: %s splited[1]: %s\n", splitted[0], splitted[1]);
		ft_remove_if(tmp, splitted[0], &data->exp);
		ft_free_double_pointer(splitted);
	}
}

//El PATH sale como /Users/begarijo.. etc.
//Hay que cambiarlo por MiniShell, para que con estos dos
//solo salga a partir de ahí, pero aún así busque bien.
