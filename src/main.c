/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/23 12:24:25 by marirodr         ###   ########.fr       */
=======
/*   Updated: 2023/08/23 12:31:50 by begarijo         ###   ########.fr       */
>>>>>>> 6b30b977f13327ad2e77b01c272ad07198e4f5c6
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
	data->bool_exp = 0;
	data->argc = 0;
	return (data);
}

void	ft_start_minishell(t_data *data)
{
	while(1)
	{
		data->input = readline("PutaShell> ");
		if (data->input == NULL)
		{
			printf("Eres un cuadro, CHAO\n");
			break ;
		}
		add_history(data->input);
		data->args = ft_split(data->input, ' ');
		data->argc = ft_double_pointer_len(data->args);
<<<<<<< HEAD
		printf("Argc: %d\n", data->argc); //borrar en un futuro
=======
>>>>>>> 6b30b977f13327ad2e77b01c272ad07198e4f5c6
		if (ft_is_builtin(data->args))
			ft_do_builtins(data->args, data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	using_history();
	data = ft_init_data(env);
	printf("Ctrl+D para salir.\n");
	ft_start_minishell(data);
	free(data->input);
	clear_history();
	return (0);
}
