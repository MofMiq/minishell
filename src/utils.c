/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:51:25 by begarijo          #+#    #+#             */
/*   Updated: 2023/08/23 12:07:23 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_double_pointer_len(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
		i++;
	return (i);
}
