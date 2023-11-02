/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:24:47 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/02 18:52:43 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Locates the first occurrence of c (converted to a char) in the string pointed
to by s. The terminating null character is considered to be part of the string;
therefore if c is '\0', the functions locate the terminating '\0'.*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if ((*ptr) == (char)c)
			return (ptr);
		ptr++;
	}
	if ((char)c == *ptr)
		return (ptr);
	return (0);
}

/*    size_t i;

    i = 0;
    while (s[i])
    {
        if (str[i] == (char)c)
            return ((char *)&s[i]);
        i++;
    }
    if ((char)c == s[i])
        return ((char *)&s[i]);
    return (NULL);*/