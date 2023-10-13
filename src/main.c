/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/13 15:37:18 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_check_type(t_data *data)
{
	t_token	*last;

	ft_init_parse(data);
	last = ft_last_token(data->token);
	if (last->type == PIPE)
		return (ft_free_token(data->token, data), ft_putstr_fd("No has cerrao el pipe\n", data->fdout));
	if (ft_one_bad_arg(data))
		return (ft_free_token(data->token, data));
	if (ft_bad_redi(data->token, data->fdout))
		return (ft_free_token(data->token, data));
	else if (data->token->type == S_QUOTES || data->token->type == D_QUOTES)
	{
		ft_putstr_fd("bash: ", data->fdout);
		ft_putstr_fd(data->token->str, data->fdout);
		ft_putstr_fd(": command not found\n", data->fdout);
	}
	ft_process_pipeline(data, ft_count_pipes(data->token));
	
	while (data->token->prev != NULL)
		data->token = data->token->prev;
	ft_free_token(data->token, data);
}
	//esto es como iba antes del ft_process_pipeline
	// else if (data->token->type == BUILTIN)
	// 	ft_do_builtins(data, data->token->str);
	// else if (data->token->type != BUILTIN && data->args)
	// {
	// 	ft_launch_exec(data);
	// 	ft_putstr_fd("que quiereh\n", data->fdout);
	// }

void	ft_start_minishell(t_data *data)
{
	while (1)
	{
		ft_signal();
		data->input = readline("\x1b[96mPutaShell> \x1b[0m");
		ft_signal_proc();
		if (data->input == NULL)
		{
			ft_putstr_fd("Eres un cuadro, CHAO\n", data->fdout);
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if ((ft_is_closed(data->input, '\'') % 2 != 0)
				|| (ft_is_closed(data->input, '\"') % 2 != 0))
				ft_putstr_fd("No has cerrao comillas chula\n", data->fdout);
			else if (!ft_is_all_space(data->input))
				ft_check_type(data);
		}
		free(data->input);
	}
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	// atexit(ft_leaks);
	t_data	*data;

	(void)argc;
	(void)argv;
	//ft_display_banner();
	using_history();
	data = ft_init_data(env, argv);
	ft_start_minishell(data);
	ft_free_all(data);
	free(data);
	return (0);
}

void	ft_display_banner(void)
{
	ft_printf("\n\t%s ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    \
			%s\n", RED, END);
	ft_printf("\t%s▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \
			%s \n", RED, END);
	ft_printf("\t%s▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \
			%s \n", RED, END);
	ft_printf("\t%s▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \
			%s\n", RED, END);
	ft_printf("\t%s▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒	\
			%s\n", RED, END);
	ft_printf("\t%s░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\
			%s\n", RED, END);
	ft_printf("\t%s░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\
			%s\n", RED, END);
	ft_printf("\t%s░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \
			%s\n", RED, END);
	ft_printf("\t%s       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\
			%s\n\n", RED, END);
}
