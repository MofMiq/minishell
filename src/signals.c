/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:18:06 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/30 19:12:10 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <termios.h>

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

// void	ft_init_sig(int sig)
// {
// 	struct termios	input;

// 	if (sig == SIGINT)
// 	{
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		signal(SIGINT, ft_init_sig);
// 	}
// 	tcgetattr(STDIN_FILENO, &input);
// 	//input.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &input);
// }
