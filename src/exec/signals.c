/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:18:06 by begarijo          #+#    #+#             */
/*   Updated: 2023/09/28 19:27:19 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// SIGUE SIN FUNCIONAR PERO TENGO POR FIN UNA PUTA TEORIA

void	ft_handler(int sig)
{
	pid_t	child;

	(void)sig;
	child = fork();
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// if (ft_active() == 0)
	// 	rl_redisplay();
}
// #include <signal.h>
// #include <stdlib.h>
// #include <stdio.h>

// static volatile sig_atomic_t keep_running = 1;

// static void sig_handler(int _)
// {
//     (void)_;
//     keep_running = 0;
// }

// int main(void)
// {
//     signal(SIGINT, sig_handler);

//     while (keep_running)
//         puts("Still running...");

//     puts("Stopped by signal `SIGINT'");
//     return EXIT_SUCCESS;
// }