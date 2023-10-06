/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:47 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/05 18:09:53 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_token_cat(t_token *aux, t_token *first, int len, int i)
{
	char	*tmp;

	while (aux && aux->space == 0)
	{
		len += ft_strlen(aux->str);
		aux = aux->next;
	}
	tmp = ft_calloc(len, sizeof(char));
	while (first && first->space == 0)
	{
		len = 0;
		while (first->str[len])
			tmp[i++] = first->str[len++];
		first = first->next;
	}
	return (tmp);
}

/*hago esta mierda despues de quitar comillas y de expandir
el dolar para que salga de puta madre cuando hay error.
quizas otra idea mas "segura" podría ser quitar los espacios de delante del
input. lo dejo aqui por si acaso.*/

int	ft_one_bad_arg(t_data *data)
{
	int		sp;
	int		len;
	char	*tmp;
	t_token	*aux;

	len = ft_strlen(data->token->str);
	aux = data->token;
	sp = 0;
	while (ft_check_space(data->input[sp]))
		sp++;
	if (sp > 0) // la estaré liando mucho aqui? a lo mejor me da problemas en otro sitio?
		data->token->space = 0;
	if (data->input[len + sp] == '\0' || data->input[len + sp] == ' '
		|| aux->type == S_QUOTES || aux->type == D_QUOTES)
		return (0);
	if (ft_strchr("'\''\"", data->input[len + sp]))
	{
		tmp = ft_token_cat(aux->next, aux, len, 0);
		ft_putstr_fd("bash: ", data->fdout);
		ft_putstr_fd(tmp, data->fdout);
		ft_putstr_fd(": command not found\n", data->fdout);
		free(tmp);
		return (1);
	}
	return (0);
}
