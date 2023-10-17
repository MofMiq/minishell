/* ************************************************************************** */
/*                                                                            */
/*                       	                                 :::      ::::::::*/
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:47:53 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/11 18:50:49 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		path = ft_strdup(node->def);
		if (path == NULL)
			return ("");
	}
	return (path);
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
	while (path_abs[i] && ft_strcmp(path_abs[i], "") != 0)
	{
		path_aux = ft_strjoin(path_abs[i], "/");
		free(path_abs[i]);
		path_abs[i] = ft_strjoin(path_aux, data->args[0]);
		free(path_aux);
		if (access(path_abs[i], F_OK) == 0 && !ft_strnstr(data->args[0], "./", 3))
		{
			free(data->args[0]);
			data->args[0] = ft_strdup(path_abs[i]);
			break ;
		}
		i++;
	}
	ft_free_double_pointer(path_abs);
}

/*aqui es donde esta la chicha: creamos un proceso hijo donde vamos tanto
-ahora si- redirigir los fds de entrada y salida al "pipe" y luego ejecutar
el programa/comando con execve. 
con dup2() lo que hacemos es duplicar un fd existente en uno especifico
-el primer parametro en el segundo-, cerrando el segundo primero que todo.
Desde un punto de vista personal y mas visual vamos hacer que el primer fd
apunte a donde del segundo, haciendo que que la informacion se transmita
desde otros sitos (si vamos cerrando fds, claro.)*/

int	ft_env_size(t_elist *elist)
{
	t_elist	*aux;
	int		i;

	i = 0;
	aux = elist;
	while (elist)
	{
		elist = elist->next;
		i++;
	}
	elist = aux;
	return (i);
}

char	**ft_reconvert_env(t_elist *elist)
{
	char	*tmp;
	char	*tmp2;
	t_elist	*aux;
	int		i;
	char	**res;

	i = 0;
	aux = elist;
	res = (char **)ft_calloc(ft_env_size(elist) + 1, (sizeof(char *)));
	if (!res)
		return (NULL);
	while (elist || res[i] != NULL)
	{
		tmp = ft_strjoin(elist->name, "=");
		tmp2 = ft_strjoin(tmp, elist->def);
		res[i] = ft_strdup(tmp2);
		i++;
		elist = elist->next;
		free(tmp);
		free(tmp2);
	}
	elist = aux;
	return (res);
}

void	ft_launch_exec(t_data *data)
{
	int	stat;

	data->child = fork();
	if (ft_is_builtin(data->args[0]) == 8)
		data->lvl += 1;
	if (data->child == 0)
	{
		ft_exec_from_path(data);
		// int i = 0;
		// while (data->args[i])
		// {
		// 	printf("%sen ft_launch_exec data->args[%i]: %s%s\n", BLUE, i, data->args[i], END);
		// 	i++;
		// }
		// printf("%sen ft_launch_exec data->fdin: %d / data->fdout: %d%s\n", BLUE, data->fdin, data->fdout, END);
		dup2(data->fdin, STDIN_FILENO);
		dup2(data->fdout, STDOUT_FILENO);
		if (execve(data->args[0], data->args, ft_reconvert_env(data->env)) == -1)
			perror(data->args[0]);
		exit(127);
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
