/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/21 17:03:10 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)env;
	using_history();
	printf("Ctrl+D para salir.\n");
	while (1)
	{
		input = readline("PutaShell> ");
		if (input == NULL)
		{
			printf("Eres un cuadro, CHAO\n");
			break ;
		}
		add_history(input);
		printf("Efectivamente has ingresado: %s\n", input);
	}
	free(input);
	clear_history();
	return (0);
}
