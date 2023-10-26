/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:57 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/26 16:29:42 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*aqui vamos a ver si en el input existe un pipe/redireccion o no y decidir
a cuales fds tenemos que redirigir tanto la extrada como la salida de datos.
al iniciar el programa (ft_init) las todo esta en los valores predefinidos.
una vez entramos aqui por primera vez -cada vez que tengamos un nuevo input-
redasignamos la entrada al valor predeterminado (teclado) por si acaso de una
vez anterior la hemos "cambiado" de sitio o cerrado.
luego ejecutamos pipe, que lo que va ga hacer es coger dos fds libres y para
que tengamos una nueva parte lectora y otra escritora -ojo no desde la pers-
pectiva del pipe, sino desde los procesos; hacia dode debe estribir un proceso
y desde donde debe leer otro.-
1) tanto si no hay pipe como si hemos llegado al ultimo comando de la pipline
reasignamos nuestra variable a la salida estandar (STDOUT_FILENO / 1) y cerra-
mos la parte lectora por que ya habremos recibido la info desde x y asi evita-
petar los fds.
2) si hay pipe reasignamos la salida a la nueva que hemos creado (fdout->fd[1])
a esa parte donde hemos "guardado" el resultado del anterior comando.
cuando "volvemos" a esta funcion despues de haber hecho toda la vaina, cerramos
el nuevo fd de escritura (fd[1]) para que no se quede esperando a recibir mas
datos por otro lado (desde el teclado). si eso ocurriera tendriamos que enviar
señal y ya funcionaria regu.
redirgimos por si acaso no volvemos a entrar aqui nuestra variable al nuevo fd
lector(fd[0]) y que el proceso lea desde ahi y nos desde el teclado.*/

void	ft_process_pipeline(t_data *data, int c_pipes)
{
	int		i;

	i = 0;
	data->curr_tkn = data->token;
	while (i <= c_pipes && data->curr_tkn)
	{
		ft_change_pipes_fds(data, i, c_pipes);
		if (data->curr_tkn->next != NULL)
			data->curr_tkn = data->curr_tkn->next;
		data->token = data->curr_tkn;
		ft_free_double_pointer(data->args);
		data->go = 0;
		i++;
	}
	ft_close_fds(data, 3);
}

void	ft_change_pipes_fds(t_data *data, int i, int c_pipes)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		data->exit_status = 1;
	}
	if (c_pipes == i)
	{
		data->fdout = STDOUT_FILENO;
		ft_begin_redi(data);
		close(fd[0]);
	}
	else
	{
		data->fdout = fd[1];
		ft_begin_redi(data);
	}
	close(fd[1]);
	data->fdin = fd[0];
}
/*en esta funcion basicamente vamos a buscar si hay una redireccion o no en el
input, independientemente de si hay pipe o no. vamos a coger todos los tokens
hasta una nueva redireccion y en ese caso parar ahi para que solo reconvertamos
los  token previos en char ** . en caso de que haya redireccion vamos a ir a
una funcion que que vuelva a redirigir las salidas o entradas en funcion de 
cual se y luego ejecutar su movida. en otro caso, comprobamos si los tokens
son builtin o no para ir a segun que sito.*/

void	ft_begin_redi(t_data *data)
{
	int	flag;

	flag = ft_advance_n_reconvert(data);
	if (flag == 1)
		ft_what_redi(data);
	if (data->args[0] == NULL || data->go == 1)
		return ;
	if (data->token->type == BUILTIN)
		ft_do_builtins(data, data->token->str);
	else
		ft_launch_exec(data);
}

int	ft_advance_n_reconvert(t_data *data)
{
	int	flag;

	flag = 0;
	if (data->curr_tkn->type == PIPE)
	{
		data->curr_tkn = data->curr_tkn->next;
		data->token = data->curr_tkn;
	}
	ft_reconvert_token(data);
	while (data->curr_tkn && data->curr_tkn->type != PIPE)
	{
		if (data->curr_tkn->type >= OUT && data->curr_tkn->type <= HERE_DOC)
		{
			flag = 1;
			break ;
		}
		if (data->curr_tkn->next == NULL)
			break ;
		data->curr_tkn = data->curr_tkn->next;
	}
	return (flag);
}

/*esta funcion cierra todos los fd cuando se llama al final de
ft_process_pipeline, es decir una vez ya hemos terminado de leer el input por
completo. ademas se resetan los valores de data->fdin y data->fdout a los
valores originales, 0 y 1 respectivamente.*/

void	ft_close_fds(t_data *data, int limit)
{
	if (data->fdin == STDIN_FILENO && data->fdout == STDOUT_FILENO)
		return ;
	while (data->fdin >= limit)
	{
		close(data->fdin);
		data->fdin--;
	}
	data->fdin = STDIN_FILENO;
	while (data->fdout >= limit)
	{
		close(data->fdout);
		data->fdout--;
	}
	data->fdout = STDOUT_FILENO;
}
