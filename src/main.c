/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/06 10:41:02 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

			//Debugeo de mierdas
			// int i = 0;
			// while (data->args[i])
			// {
			// 	ft_printf("en ft_start_minishell: %s\n", data->args[i]);
			// 	i++;
			// }

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
				data->input = ft_ignore_quotes(data->input); //aplicar esto aqui rompe el echo de belen, no se si algo mas
			data->args = ft_split(data->input, ' ');
			//Debugeo de mierdas
			int i = 0;
			while (data->args[i])
			{
				printf("en ft_start_minishell: %s\n", data->args[i]);
				i++;
			}
			data->argc = ft_double_pointer_len(data->args);
			ft_find_dollar(data->args, data);
			i = 0;
			while (data->args[i])
			{
				printf("en ft_start_minishell despues de $: %s\n", data->args[i]);
				i++;
			}
			if (ft_is_builtin(data))
				ft_do_builtins(data);
			ft_free_double_pointer(data->args);
			free(data->input);
		}
	}
}
//printf("ft_start_minishell: data->args: %s / %s\n", data->args[0], data->args[1]);

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
