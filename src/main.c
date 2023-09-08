/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/08 17:42:35 by begarijo         ###   ########.fr       */
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
			// esta parte la quito ahora mismo para evitar mierdas, despues de parseo adaptamos
			// if (ft_there_is_quote(data->input) != (int)ft_strlen(data->input))
			// 	data->input = ft_ignore_quotes(data->input); //aplicar esto aqui rompe el echo de belen, no se si algo mas
			// ft_find_dollar(data->args, data);

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
			ft_init_parse(data);
			//probablemente esto lo tenga que meter en otra funcion que "redireccione" segun los tipos de los tokens
			if (data->token->type == BUILTIN)
				ft_do_builtins(data, data->token->str);
			else if (data->token->type != BUILTIN && data->args)
      {
				printf("que quiereh\n");
				//printf("bash: %s: command not found\n", data->token->str);
      }
			ft_free_token(data->token, data);
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
	data = ft_init_data(env, argv);
	ft_start_minishell(data);
	printf("si te sales imprimes????\n");
	ft_free_all(data);
	free(data);
	return (0);
}
