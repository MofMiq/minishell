/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:50:11 by marirodr          #+#    #+#             */
/*   Updated: 2023/03/30 20:17:57 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_remove_if(t_list **begin, void *d_r, int (*cmp)())
{
	t_list	*current;

	if ((begin == NULL) || (*begin == NULL))
		return ;
	current = *begin;
	if (((cmp)(current->data, d_r)) == 0)
	{
		*begin = current->next;
		free(current);
		ft_list_remove_if(begin, d_r, cmp);
	}
	current = *begin;
	ft_list_remove_if(&current->next, d_r, cmp);
}
