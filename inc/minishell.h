/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:55:53 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/22 16:25:55 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_elist
{
	char			*name;
	char			*def;
	struct s_elist	*prev;
	struct s_elist	*next;
}	t_elist;

typedef struct s_data
{
	char	*input;
	t_elist	*env;
}	t_data;

//list_utils.c
t_elist	*ft_new_node(char **splited);
t_elist	*ft_last_node(t_elist *node);
t_elist	*ft_add_back(t_elist **env, t_elist *new);
t_elist	*ft_copy_env(char **env);
void	ft_print_list(t_elist *env);

#endif
