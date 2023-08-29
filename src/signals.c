/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:18:06 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/29 19:05:30 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

/*
void	ft_getter(int i, t_data *data)
{
	static int	active;

	active = i;
	data->sig = &active;
}

int	ft_setter(t_data *data)
{
	int	active;

	active = *(data->sig);
	return (active);
}
*/

void	ft_ignore_sigquit(void)
{
	struct sigaction	sigq;
	
	printf("Aquí llegas?\n");
	ft_memset(&sigq, 0, sizeof(sigq));
	sigq.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigq, NULL);
}


/*No entiendo muy bien como va esto, hacer pruebas cambiando cosas*/
