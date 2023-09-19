/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:18:06 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/19 18:23:11 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Al ejecutar de nuevo ./minishell, cuando intentas hacer un CTRL + D parece
// que hay problemas. Ademas no funcionan los builtins en el proceso hijo????
// Seguramente sea del exec

void	ft_init_sig(void)
{
	struct sigaction	sig;

	ft_ignore_sigquit();
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = &ft_restart_input;
	sigaction(SIGINT, &sig, NULL);
}

void	ft_restart_input(int sig)
{
	(void)sig;
	printf("\nHas hecho CTRL + C\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_ignore_sigquit(void)
{
	struct sigaction	sigq;

	ft_memset(&sigq, 0, sizeof(sigq));
	sigq.sa_handler = SIG_IGN;
	sigemptyset(&sigq.sa_mask);
	sigq.sa_flags = 0;
	sigaction(SIGQUIT, &sigq, NULL);
}
