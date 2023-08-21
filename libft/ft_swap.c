/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:32:33 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/30 11:04:49 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*int main()
{
	int a;
	int b;
	int *pa;
	int *pb;

	a = 42;
	b = 3;
	pa = &a;
	pb = &b;

	printf("%d %d \n", a, b);
	ft_swap(pa, pb);
	printf("%d %d \n", a, b);
}*/
