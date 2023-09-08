/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/08 11:48:53 by marirodr         ###   ########.fr       */
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
	t_elist	*tmp; //este tmp nos sigue sirviendo??

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
			//printf("IMPRIMIENDO EL INPUT QUE TENGO QUE PARSEAR: %s", data->input);
			ft_init_parse(data);
			//data->args = ft_split(data->input, ' ');
			//data->argc = ft_double_pointer_len(data->args);
			//para que no pete comento
			/*if (ft_is_builtin(data))
				ft_do_builtins(data);
			ft_free_double_pointer(data->args);*/
			//probablemente esto lo tenga que meter en otra funcion que "redireccione" segun los tipos de los tokens
			//if (data->token->type == BUILTIN)
			// 	ft_do_builtins(data, data->token->str);
			ft_free_token(data->token);
			data->token = NULL;
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
	data = ft_init_data(env, argv);
	ft_start_minishell(data);
	printf("si te sales imprimes????\n");
	ft_free_all(data);
	free(data);
	return (0);
}
