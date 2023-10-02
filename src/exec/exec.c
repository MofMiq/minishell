/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:47:53 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/02 18:08:17 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Arreglar para que al ejecutar de nuevo ./minishell los builtins funcionen
// además  hay que arreglar esta caca y ponerla en orden, faltan mogollon
// de cosillas. 
// Control de errores regu, arreglar buscar la salida correcta

char	*ft_get_path(t_data *data)
{
	char	*path;
	t_elist	*node;

	node = ft_search_node(data->env, "PATH");
	path = NULL;
	if (!node)
		ft_putstr_fd("no hay path jejejjeje\n", data->fdout);
	else
	{
		path = node->def;
		if (path == NULL)
			return ("");
	}
	return (path);
}

void	ft_create_path(t_data *data, char *path, char **path_abs)
{
	int	i;

	i = 0;
	while (path_abs[i] && ft_strcmp(path_abs[i], "") != 0)
	{
		path = ft_strjoin(path_abs[i], "/");
		free(path_abs[i]);
		path_abs[i] = ft_strjoin(path, data->args[0]);
		free(path);
		if (access(path_abs[i], F_OK) == 0
			&& !ft_strnstr(data->args[0], "./", 3))
		{
			free(data->args[0]);
			data->args[0] = ft_strdup(path_abs[i]);
			break ;
		}
		i++;
	}
}

void	ft_exec_from_path(t_data *data)
{
	char	*path_aux;
	char	**path_abs;
	int		i;

	path_aux = ft_get_path(data);
	path_abs = ft_split(path_aux, ':');
	i = 0;
	if (ft_strcmp(path_aux, "") != 0)
		free(path_aux);
	ft_create_path(data, path_aux, path_abs);
	ft_free_double_pointer(path_abs);
}

// Comprobar que se sale bien, buscar como hacer bien el proceso
// Cuando se reejecute: SEÑALES? EJECUTABLES 
// La salida tiene que ir por otro lado, buscar en man WIFEXIT?

void	ft_launch_exec(t_data *data)
{
	int	stat;

	data->child = fork();
	/*a partir de aqui seria la funcion childprocess*/
	if (data->child == 0)
	{
		ft_exec_from_path(data);
		if (execve(data->args[0], data->args, &data->env->name) == -1)
			perror("PATH");
		else
			ft_free_all(data);
	}
	else if (data->child < 0)
		perror(data->args[0]);
	else
		waitpid(data->child, &stat, WUNTRACED);
}
