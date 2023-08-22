/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/22 16:47:49 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;
	char	**args;

	(void)argc;
	(void)argv;
	data = (t_data *)malloc(sizeof(t_data));
	using_history();
	printf("Ctrl+D para salir.\n");
	data->env = ft_copy_env(env);
	//ft_print_list(data->env);
	while (1)
	{
		input = readline("PutaShell> ");
		if (input == NULL)
		{
			printf("Eres un cuadro, CHAO\n");
			break ;
		}
		add_history(input);
		args = ft_split(input, ' '); 
		if (ft_is_builtin(args))
			ft_do_builtins(args);
	//	printf("Efectivamente has ingresado: %s\n", input);
	}
	free(input);
	clear_history();
	return (0);
}
