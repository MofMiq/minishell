/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/24 11:31:33 by marirodr         ###   ########.fr       */
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
	/*printf("[1]Nodo: %s\n", data->env->name); //1o nodo
	printf("[1]Next: %s\n", data->env->next->name); //2er nodo desde el 1o
	printf("[1]Prev: %s\n", data->env->prev->name); //NULL nodo desde el 1o
	printf("------------\n");
	printf("[2]Nodo: %s\n", data->env->next->name); //2o nodo
	printf("[2]Next: %s\n", data->env->next->next->name); //3er nodo desde el 2o
	printf("[2]Prev: %s\n", data->env->next->prev->name); //1er nodo desde el 2o
	printf("------------\n");
	printf("[3]Nodo: %s\n", data->env->next->next->name); //3o nodo
	printf("[3]Next: %s\n", data->env->next->next->next->name); //4er nodo desde el 3o
	printf("[3]Prev: %s\n", data->env->next->next->prev->name); //2er nodo desde el 3o
	printf("------------\n");
	printf("[4]Nodo: %s\n", data->env->next->next->next->name); //3o nodo
	printf("[4]Next: %s\n", data->env->next->next->next->next->name); //4er nodo desde el 3o
	printf("[4]Prev: %s\n", data->env->next->next->next->prev->name); //2er nodo desde el 3o
	printf("------------\n");
	data->env = ft_last_node(data->env);
	printf("Despues de aplicar ft_last_node: %s\n", data->env->name);
	//data->env = data->env->next->next->next->next;
	//printf("Despues mover la lista cinco posiciones: %s\n", data->env->name);
	data->env = ft_first_node(data->env);
	printf("Despues de aplicar ft_first_node: %s\n", data->env->name);*/
	ft_start_minishell(data);
	free(data->input); //free toda la estructura y lista
	clear_history();
	return (0);
}
