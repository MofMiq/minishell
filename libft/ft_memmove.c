/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:13:29 by marirodr          #+#    #+#             */
/*   Updated: 2022/10/05 18:23:55 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Copies len bytes from string src to string dst. The two strings may overlap;
the copy is always done in a non-destructive manner.
Returns the original valuen of dst.*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dst;
	if (!dst && !src)
		return (0);
	i = 0;
	if (d > s)
		while (len-- > 0)
			d[len] = s[len];
	else if (d < s)
		ft_memcpy(dst, src, len);
	return (dst);
}
