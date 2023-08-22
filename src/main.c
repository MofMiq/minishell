/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/22 11:43:30 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**args;

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
		args = ft_split(input, ' '); 
		ft_echo(args);
	//	printf("Efectivamente has ingresado: %s\n", input);
	}
	free(input);
	clear_history();
	return (0);
}
