/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:38:01 by marirodr          #+#    #+#             */
/*   Updated: 2022/10/05 16:55:36 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Locates the last ocurrence of c (converted to a char) in the string s.
If c is '\0', locates the terminating '\0'.*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i--;
	}
	return (NULL);
}
