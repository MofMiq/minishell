/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/25 12:22:45 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	*ft_init_data(char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->env = ft_copy_env(env);
	data->input = NULL;
	data->args = NULL;
	data->bool_exp = 0;
	data->argc = 0;
	return (data);
}

void	ft_start_minishell(t_data *data)
{
	while (1)
	{
		data->input = readline("\x1b[96mPutaShell> \x1b[0m");
		if (data->input == NULL)
		{
			printf("Eres un cuadro, CHAO\n");
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			data->args = ft_split(data->input, ' ');
			data->argc = ft_double_pointer_len(data->args);
			if (ft_is_builtin(data))
				ft_do_builtins(data);
		}
	}
}

/*void	ft_leaks(void)
{
	system("leaks -q minishell");
}*/

int	main(int argc, char **argv, char **env)
{
	//atexit(ft_leaks); //buscar leaks
	t_data	*data;

	(void)argc;
	(void)argv;
	using_history();
	data = ft_init_data(env);
	ft_start_minishell(data);
	free(data->input); //free toda la estructura y lista
	clear_history();
	return (0);
}
