/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/04 17:00:07 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_start_minishell(t_data *data)
{
	t_elist	*tmp;

	tmp = data->env;
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
			if (ft_there_is_quote(data->input) != (int)ft_strlen(data->input))
				data->input = ft_ignore_quotes(data->input);
			printf("en ft_start_minishell: data->input: %s\n", data->input);
			data->args = ft_split(data->input, ' ');
			data->argc = ft_double_pointer_len(data->args);
			if (ft_is_builtin(data))
				ft_do_builtins(data);
			ft_free_double_pointer(data->args);
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
	atexit(ft_leaks);
	t_data	*data;

	(void)argc;
	(void)argv;
	using_history();
	data = ft_init_data(env);
	ft_start_minishell(data);
	printf("si te sales imprimes????\n");
	ft_free_all(data);
	free(data);
	return (0);
}
