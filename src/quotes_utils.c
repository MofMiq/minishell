/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:59:13 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/18 12:47:59 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*No te asustes Belen, no me he metido ultra a full con tema comillas. mirando
el export me dado cuenta de que si las dobles comillas estan bien puestas, las
ignora completamente y se guardan tal cual, por lo que he hecho unas funciones 
simples para detectar y quitar las comillas del data->input. sé que están raras
y a lo mejor en un futuro hay que modificarlas pero para ir cerrando cosillas
de los builtins*/

int	ft_is_quote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

int	ft_there_is_quote(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]) == 1)
			c++;
		i++;
	}
	i -= c;
	return (i);
}
