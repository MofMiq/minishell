/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/23 18:26:38 by begarijo         ###   ########.fr       */
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
		data->argc = ft_double_pointer_len(data->args);
		if (ft_is_builtin(data))
			ft_do_builtins(data);
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
