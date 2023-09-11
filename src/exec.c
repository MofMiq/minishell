/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:47:53 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/11 18:48:37 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Comprobar que sale bien del waitpid;
//ft_free_all creo que esta como el culo ahi, pero creo 
// que hay que liberar por separado?=????

void	ft_exec_from_path(t_data *data);

/*en execve hay que pasarle en lugar de data->env un char*const*
 * habría que ver como cambiar eso, y a parte hacer la función de exec from path*/

void	ft_launch_exec(t_data *data)
{
	int	stat;

	data->child = fork();
	if (data->child == 0)
	{
		ft_exec_from_path(data);
		if (execve(data->args[0], data->args, data->env) == -1)
			printf("Errorsito\n");
		ft_free_all(data);
	}
	else if (data->child < 0)
		perror(data->args[0]);
	else
		waitpid(data->child, &stat, WUNTRACED);
}
