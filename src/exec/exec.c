/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:47:53 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/11 13:50:27 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Arreglar para que al ejecutar de nuevo ./minishell los builtins funcionen
// además  hay que arreglar esta caca y ponerla en orden, faltan mogollon
// de cosillas. 
// Control de errores regu, arreglar buscar la salida correcta

//ft_strdup para arreglar los problemas de memoria!!!

char	*ft_get_path(t_data *data)
{
	char	*path;
	t_elist	*node;

	node = ft_search_node(data->env, "PATH");
	path = NULL;
	if (!node)
		ft_putstr_fd("", data->fdout);
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
		//printf("PATH AUXILIAR: %s\n", path);
		path_abs[i] = ft_strjoin(path, data->args[0]);
		//printf("PATH ABSOLUTO: %s", path_abs[i]);
		free(path);
		if (access(path_abs[i], F_OK) == 0
			&& !ft_strnstr(data->args[0], "./", 3))
		{
			free(data->args[0]);
			data->args[0] = ft_strdup(path_abs[i]);
			break ;
		}
		else if (access(path_abs[i], F_OK) != 0)
			printf("POSNOECISTE\n");
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

void	ft_file_exists(t_data *data)
{
	if (access(data->args[0], F_OK) == 0)
	{
		if (ft_strnstr(data->args[0], "./", 3) == 0 && ft_strnstr(data->args[0], "/", 2) == 0)
			ft_putstr_fd("bash : command not found \n", data->fdout);
	}
}

/*aqui es donde esta la chicha: creamos un proceso hijo donde vamos tanto
-ahora si- redirigir los fds de entrada y salida al "pipe" y luego ejecutar
el programa/comando con execve. 
con dup2() lo que hacemos es duplicar un fd existente en uno especifico
-el primer parametro en el segundo-, cerrando el segundo primero que todo.
Desde un punto de vista personal y mas visual vamos hacer que el primer fd
apunte a donde del segundo, haciendo que que la informacion se transmita
desde otros sitos (si vamos cerrando fds, claro.)*/

/*CUANDO NO EXISTE UN COMANDO BORRA EL PATH, ¿?¿?¿?¿?¿?¿?¿?¿?¿*/

void	ft_launch_exec(t_data *data)
{
	int	stat;

	data->child = fork();
	if (data->child == 0)
	{
		// ft_file_exists(data);
		ft_exec_from_path(data);
		// int i = 0;
		// while (data->args[i])
		// {
		// 	printf("%sen ft_launch_exec data->args[%i]: %s%s\n", PINK, i, data->args[i], END);
		// 	i++;
		// }
		//printf("%sen ft_launch_exec data->fdin: %d / data->fdout: %d%s\n", BLUE, data->fdin, data->fdout, END);
		dup2(data->fdin, STDIN_FILENO);
		dup2(data->fdout, STDOUT_FILENO);
		if (execve(data->args[0], data->args, &data->env->name) == -1)
			perror(data->args[0]);
		else
			ft_free_all(data);
	}
	else if (data->child < 0)
		perror(data->args[0]);
	else
	{
		waitpid(data->child, &stat, WUNTRACED);
		if (data->child > 0)
		{
			if (WIFEXITED(stat))
				data->exit_status = WEXITSTATUS(stat);
		}
	}
}

		// //printf("%sen ft_launch_exec data->cur_token: %s%s\n", PINK, data->curr_tkn->str, END);