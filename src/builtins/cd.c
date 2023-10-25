/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:25:39 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/25 19:31:29 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*función stat !!!!!!!!!*/
//printf("prueba a imprimir st_mode aver que pasa\n");

int	ft_special_dir(t_data *data)
{
	struct stat	file_st;
	int			per;

	lstat(data->args[1], &file_st);
	per = file_st.st_mode;
	//printf("file_st->en decimal: %d / en octal: %o\n", file_st.st_mode, file_st.st_mode);
	//esta funcion hay que meterla en otro sito
	// o llamarla desde builtins!!!!
	if (per == 16448 || per == 16449 || per == 16456 || per == 16457
		|| per == 16576 || per == 16600 || per == 16603)
	{
		ft_putstr_fd("bash: cd: permission denied\n", data->fdout);
		data->exit_status = 2;
		return (1);
	}
	return (0);
}

void	ft_change_dir(t_data *data, char *owd)
{
	char		*nwd;

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

	if (ft_special_dir(data) == 0)
		return ;
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
			data->exit_status = 0;
		}
		else
			ft_putstr_fd("bash: cd: HOME not set\n", data->fdout);
			data->exit_status = 127; //que haces aqui no deberia est entre parentesis o identado
	}
	else if (chdir(data->args[1]) != 0)
	{
		ft_putstr_fd("bash: cd: permission denied\n", data->fdout);
		data->exit_status = 2;
	}
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
		data->exit_status = 0;
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
		splitted = ft_alt_split(var_env, '=');
		if (ft_list_cmp(data->env, splitted[0]) == 0)
			ft_update_list(data->env, splitted[1], splitted[0]);
		else if (ft_list_cmp(data->env, splitted[0]) != 0)
			ft_add_back(&data->env, ft_new_node(splitted));
		ft_free_double_pointer(splitted);
	}
	else if (i == 2)
	{
		tmp = data->exp;
		splitted = ft_alt_split(var_env, '=');
		ft_remove_if(tmp, splitted[0], &data->exp);
		ft_free_double_pointer(splitted);
	}
}
