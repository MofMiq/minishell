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

/*In this function, we execute external commands from the PATH environment
variable. To do this, we create a child process where we redirect both the input
and output file descriptors to the 'pipe' and then execute the program/command
with 'execve()' while the parent process waits for it to finish.

With 'dup2(),' we duplicate an existing file descriptor into a specific one,
closing the second one first. From a personal and more visual perspective, we
make the first file descriptor point to where the second one does, allowing
information to be transmitted from other sources (if we are closing file
descriptors, of course).*/

void	ft_launch_exec(t_data *data)
{
	int	stat;

	data->child = fork();
	if (ft_is_builtin(data->args[0]) == 8)
		data->lvl += 1;
	if (data->child == 0)
	{
		ft_exec_from_path(data);
		ft_running_exec(data);
	}
	else if (data->child < 0)
		data->exit_status = 1;
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

/*This function compares the argument from the input with all the paths in the
PATH environment variable. If it is found, we replace that argument with the full
path so that we can execute it successfully with 'execve().'
For example:  > ls => /bin/ls */

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
		if (access(path_abs[i], F_OK) == 0
			&& !ft_strnstr(data->args[0], "./", 3))
		{
			free(data->args[0]);
			data->args[0] = ft_strdup(path_abs[i]);
			break ;
		}
		i++;
	}
	ft_free_double_pointer(path_abs);
}

/*With this function, we retrieve the PATH environmental variable and copy
its contents into a string.*/

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

void	ft_running_exec(t_data *data)
{
	char	**env_arg;

	env_arg = ft_reconvert_env(data->env);
	dup2(data->fdin, STDIN_FILENO);
	dup2(data->fdout, STDOUT_FILENO);
	if (execve(data->args[0], data->args, env_arg) == -1)
	{
		ft_putstr_fd("bash: ", data->fdout);
		ft_putstr_fd(data->args[0], data->fdout);
		ft_putstr_fd(": command not found\n", data->fdout);
		ft_free_double_pointer(env_arg);
		data->exit_status = 127;
	}
	exit(127);
}

/*This function reconvert the linked list of environmental variables to
** char because we need that format for execve().*/

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
