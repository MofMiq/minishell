/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:57 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/26 18:10:48 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_redi_output(t_data *data, t_token *token)
{
	(void)data;
	(void)token;
	printf("hacer la redireccion del output\n");
	// char	*name;
	// int i;
	// int	fd;

	// i = 0;
	// while (token->str[i] == '>' || token->str[i] == ' ')
	// 	i++;
	// name = ft_substr(token->str, i, (ft_strlen(token->str) - 1));
	// printf("en ft_redi_output: token->str: %s y token->type: %d\n", token->str, token->type);
	// printf("en ft_redi_output: name: %s\n", name);
	// fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// if (fd == -1)
	// {
	// 	perror("fallo en open");
	// 	exit(EXIT_FAILURE);
	// }
	// if (dup2(fd, STDOUT_FILENO) == -1)
	// {
	// 	perror("fallo en dup");
	// 	exit(EXIT_FAILURE);
	// }
	// if (close(fd) == -1)
	// {
	// 	perror("fallo en close");
	// 	exit(EXIT_FAILURE);
	// }
	// printf("Hello world\n");
	// free(name);
}
