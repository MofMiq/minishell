/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_at_exit_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:31:52 by juan-aga          #+#    #+#             */
/*   Updated: 2023/08/28 14:26:50 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_leaks.h"

void	ft_count_free(t_mem_check *mem_check)
{
	t_malloc	*m;
	t_malloc	*f;

	m = mem_check->alloc;
	while (m)
	{
		f = mem_check->free;
		while (f)
		{
			if (!ft_strcmp_ja(m->p, f->p))
				m->num_free += 1;
			f = f->next;
		}
		m = m->next;
	}
}

void	ft_count_alloc(t_malloc *lst1, t_malloc *lst2)
{
	t_malloc	*m;
	t_malloc	*d;

	m = lst1;
	while (m)
	{
		d = lst2;
		while (d)
		{
			if (!ft_strcmp_ja(m->p, d->p))
				m->num_alloc += 1;
			d = d->next;
		}
		m = m->next;
	}
}

int	ft_strcmp_ja(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	if (s1[i] == s2[i])
		return (0);
	return (1);
}
