/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/22 18:27:44 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Meter bucle en otra función

t_data	*ft_init_data(char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->env = ft_copy_env(env);
	data->input = NULL;
	data->args = NULL;
	return (data);
}

int	main(int argc, char **argv, char **env)
{
//	char	*input;
//	char	**args;
	t_data	*data;

	(void)argc;
	(void)argv;
//	data = (t_data *)malloc(sizeof(t_data));
	using_history();
//	data->env = ft_copy_env(env);
	data = ft_init_data(env);
	printf("Ctrl+D para salir.\n");
	while (1)
	{
		data->input = readline("PutaShell> ");
		if (data->input == NULL)
		{
			printf("Eres un cuadro, CHAO\n");
			break ;
		}
		add_history(data->input);
		data->args = ft_split(data->input, ' '); 
		if (ft_is_builtin(data->args))
			ft_do_builtins(data->args, data);
	}
	free(data->input);
	clear_history();
	return (0);
}
