/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:39:22 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/14 11:35:31 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int i)
{
	if (!((i >= 'a' && i <= 'z')
			|| (i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9')))
		return (0);
	return (1);
}

int	ft_isalnum_plus(int i)
{
	if (!((i >= 'a' && i <= 'z')
			|| (i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9')
			|| (i == '_')))
		return (0);
	return (1);
}
