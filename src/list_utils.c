/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:38:14 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/24 11:26:36 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_elist	*ft_new_node(char **splited)
{
	t_elist	*node;

	node = (t_elist *)malloc(sizeof(t_elist));
	if (!node)
	{
		perror("Allocation problem\n");
		exit(EXIT_FAILURE);
	}
	node->name = ft_strdup(splited[0]);
	node->def = ft_strdup(splited[1]);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_elist	*ft_last_node(t_elist *node)
{
	while (node && node->next != NULL)
		node = node->next;
	return (node);
}

t_elist	*ft_penultimate_node(t_elist *lst)
{
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}

t_elist	*ft_first_node(t_elist *node)
{
	while (node && node->prev != NULL)
		node = node->prev;
	return (node);
}

t_elist	*ft_add_back(t_elist **env, t_elist *new)
{
	if (!new)
		return (NULL);
	if (*env == NULL)
		*env = new;
	else
	{
		ft_last_node(*env)->next = new;
		if ((*env)->prev == NULL)
			new->prev = ft_penultimate_node(*env);
	}
	return (*env);
}

t_elist	*ft_copy_env(char **env)
{
	int		i;
	char	**splited;
	t_elist	*elist;

	i = 0;
	elist = NULL;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		ft_add_back(&elist, ft_new_node(splited));
		i++;
	}
	ft_free_double_pointer(splited);
	return (elist);
}
