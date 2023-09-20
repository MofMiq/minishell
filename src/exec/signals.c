/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:18:06 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/20 19:00:31 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Al ejecutar de nuevo ./minishell, cuando intentas hacer un CTRL + D parece
// que hay problemas. Ademas no funcionan los builtins en el proceso hijo????
// Seguramente sea del exec

int	*g_active;

static int	ft_get_active(void)
{
	int	active;

	active = *g_active;
	return (active);
}

void	ft_sig_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (ft_get_active() == 0)
		rl_redisplay();
}

void	ft_child_process(int b)
{
	static int	active;

	active = b;
	g_active = &active;
}
