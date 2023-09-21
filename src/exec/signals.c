/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:18:06 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/21 18:20:43 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Variable global, intentar cambiarla por estatica???

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
