/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/30 16:54:09 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_start_minishell(t_data *data)
{
	t_elist	*tmp;

	tmp = data->env;
//	signal(SIGINT, ft_sig_handler);
//	signal(SIGQUIT, ft_sig_handler);
	while (1)
	{
//		ft_init_sig();
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
			ft_free_double_pointer(data->args); //testear, podría dar algunos problemas???
			free(data->input);
		}
	}
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	atexit(ft_leaks); //buscar leaks
	t_data	*data;

	(void)argc;
	(void)argv;
	using_history();
	data = ft_init_data(env);
	ft_start_minishell(data);
	ft_free_all(data);
	free(data);
	return (0);
}
