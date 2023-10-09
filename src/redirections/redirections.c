/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:01:57 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/09 14:07:16 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_count_pipes(t_token *token)
{
	int		c;
	t_token	*tmp;

	c = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			c++;
		tmp = tmp->next;
	}
	return (c);
}

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
lector(fd[0]) y que el proceso lea desde ahi y nos desde el teclado.
*/
		//debugeo
		//printf("en ft_process_pipeline DESDE IF\n");
		//printf("en ft_process_pipeline no pipe: data->fdin: %d / data->fout: %d\n", data->fdin, data->fdout);
		//printf("en ft_process_pipeline DESDE ELSE\n");
		//printf("en ft_process_pipeline si pipe: data->fdin: %d / data->fout: %d\n", data->fdin, data->fdout);
		//printf("en ft_process_pipeline: data->fdin: %d\n", data->fdin);
		//printf("%sen ft_process_launch exit_status: %d%s\n", PINK, data->exit_status, END);

void	ft_process_pipeline(t_data *data, int c_pipes)
{
	int		i;
	int		fd[2];

	i = 0;
	data->curr_tkn = data->token;
	data->fdin = STDIN_FILENO; //podra hacer esto desde otro sitio?
	while (i <= c_pipes && data->curr_tkn)
	{
		if (pipe(fd) == -1)
			perror("pipe");
		if (c_pipes == i)
		{
			data->fdout = STDOUT_FILENO;
			ft_begin_redi(data);
			close(fd[0]); //habra que cerrar esto en alguno momento no?
		}
		else
		{
			data->fdout = fd[1];
			ft_begin_redi(data);
		}
		close(fd[1]);
		data->fdin = fd[0];
		if (data->curr_tkn)
			data->curr_tkn = data->curr_tkn->next;
		ft_free_double_pointer(data->args);
		i++;
	}
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

	flag = 0;
	ft_reconvert_token(data);
	while (data->curr_tkn && data->curr_tkn->type != PIPE)
	{
		if (data->curr_tkn->type >= OUT && data->curr_tkn->type <= HERE_DOC)
		{
			flag = 1;
			break ;
		}
		data->curr_tkn = data->curr_tkn->next;
	}
	if (flag == 1)
	{
		ft_what_redi(data);
		ft_launch_exec(data);
	}
	else
	{	
		if (data->token->type == BUILTIN)
			ft_do_builtins(data, data->token->str); //tener cuidado aqui hacia que token estamos apuntando, es probable que este fatal gracias.
		else
			ft_launch_exec(data);
	}
}

void	ft_what_redi(t_data *data)
{
	t_token	*aux;

	aux = data->curr_tkn;
	if (aux->type == OUT)
		ft_out_redi(data, 0);
	else if (aux->type == APPEDEN)
		ft_out_redi(data, 1);
	else if (aux->type == IN)
		ft_input_redi(data);
	else if (aux->type == HERE_DOC)
		ft_here_doc(data);
	aux = aux->next;
}

void	ft_out_redi(t_data *data, int flag)
{
	int		new_fd;
	char	**matrix;

	matrix = ft_split(data->curr_tkn->str, ' ');
	if (flag == 0)
		new_fd = open(matrix[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		new_fd = open(matrix[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	data->fdout = new_fd;
	// if (data->fdout != STDOUT_FILENO) //esto es para cuando haya mas de una redireccion?
	// 	close(data->fdout);
	ft_free_double_pointer(matrix);
}

void	ft_input_redi(t_data *data)
{
	int		new_fd;
	char	**matrix;

	matrix = ft_split(data->curr_tkn->str, ' ');
	new_fd = open(matrix[1], O_RDONLY);
	if (new_fd == -1)
	{
		ft_putstr_fd("error opening file from fT_input_redi\n", data->fdout);
		return ;
	}
	// if (data->fdin != STDIN_FILENO) //esto es para cuando haya mas de una redireccion
	// 	close(data->fdin);
	data->fdin = new_fd;
	ft_free_double_pointer(matrix);
}

void	ft_here_doc(t_data *data)
{
	ft_putstr_fd("ni puta idea todavia de que va esto exactamente\n", data->fdout);
	return ;
}
