/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:18:06 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/17 16:40:08 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*setter y getter para poder indicar como funcionan las señales,
* añadir a este file el "childprocess", que en principio esta
* dentro de exec.c en la funcion launch*/

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
