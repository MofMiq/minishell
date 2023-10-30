/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:43:04 by begarijo          #+#    #+#             */
/*   Updated: 2023/10/30 15:42:50 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*With this funtion, we achieve two things: first, to determine if a token
previously assigned as a NO_QUOTES type is a built-in and the reassigne it; 
and second, when we finally get to execute a command, knowing whether its one of
our builti-ins or its a command that we have to search in PATH and execute with
execve() function.*/

int	ft_is_builtin(char *str)
{
	if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "ECHO")))
		return (1);
	if (!(ft_strcmp(str, "cd")) || !(ft_strcmp(str, "CD")))
		return (2);
	if (!(ft_strcmp(str, "pwd")) || !(ft_strcmp(str, "PWD")))
		return (3);
	if (!(ft_strcmp(str, "export")) || !(ft_strcmp(str, "EXPORT")))
		return (4);
	if (!(ft_strcmp(str, "unset")) || !(ft_strcmp(str, "UNSET")))
		return (5);
	if (!(ft_strcmp(str, "env")) || !(ft_strcmp(str, "ENV")))
		return (6);
	if (!(ft_strcmp(str, "exit")) || !(ft_strcmp(str, "EXIT")))
		return (7);
	if (!(ft_strcmp(str, "./minishell")))
		return (8);
	return (0);
}

/*This function simply redirect our program to other functions where we have
implemented the mandatory built-ins.

In the case of 'cd' and 'export' we have added some code here, because of 42
norm, instead of having them there, which makes more sense.
	- cd: apart from check the name, we also check with ft_special_dir if the
		directory has the correct permissions to enter.
	- export: when 'export' is the only argument, we just print environmental
		variables.*/

void	ft_do_builtins(t_data *data, char *str)
{
	int	b;

	b = ft_is_builtin(str);
	if (b == 1)
		ft_echo(data);
	else if (b == 2 && ft_special_dir(data) == 0)
		ft_cd(data, NULL);
	else if (b == 3)
		ft_pwd(data);
	else if (b == 4)
	{
		data->exit_status = 0;
		if (data->argc == 1)
			ft_print_env(data, data->env, 2);
		ft_export(data);
	}
	else if (b == 5)
		ft_unset(&data->env, &data->exp, data);
	else if (b == 6)
		ft_env(data, data->args);
	else if (b == 7)
		ft_miniexit(data);
	else if (b == 8)
		data->lvl += 1;
}

/*This function checks the permissions of the directories using the stat()
function and its stat strcuture. The ones from the first line only have execution
perimissions and the ones in the second, have both execution and write
permission. For all of them, we print one error message and avoid executing 'cd.
*/

int	ft_special_dir(t_data *data)
{
	struct stat	file_st;
	int			per;

	if (data->args[1])
	{
		lstat(data->args[1], &file_st);
		per = file_st.st_mode;
		if (per == 16448 || per == 16449 || per == 16456 || per == 16457
			|| per == 16576 || per == 16600 || per == 16603)
		{
			ft_putstr_fd("bash: cd: permission denied\n", data->fdout);
			data->exit_status = 2;
			return (1);
		}
	}
	return (0);
}
