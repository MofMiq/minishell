/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:05:18 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/29 15:45:14 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_sig_handler(int sig)
{
	signal(sig, SIG_IGN);
	printf("Has hecho CTRL + C????\n");
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit (0);
}
