/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/18 15:25:37 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			if (ft_is_closed(data->input) % 2 != 0)
				printf("No has cerrao comillas chula\n");
			else
			{
				ft_init_parse(data);
				if (data->token->type == BUILTIN)
					ft_do_builtins(data, data->token->str);
				else if (data->token->type != BUILTIN && data->args)
				{
					ft_launch_exec(data);
					printf("que quiereh\n");
					// printf("bash: %s: command not found\n", data->token->str);
				}
				ft_free_token(data->token, data);
			}
		}
		free(data->input); //para evitar leak vacio cuando solo pulsas enter
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
	data = ft_init_data(env, argv);
	ft_start_minishell(data);
	printf("si te sales imprimes????\n");
	ft_free_all(data);
	free(data);
	return (0);
}
