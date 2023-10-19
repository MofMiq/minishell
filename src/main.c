/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/19 19:02:14 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_check_type(t_data *data)
{
	if (ft_strchr("<>|", data->input[(int)ft_strlen(data->input) - 1]))
	{
		ft_putstr_fd("bash: syntax error near unexpected token\n", data->fdout);
		data->exit_status = 1;
		return ;
	}
	ft_init_parse(data);
	if (ft_bad_redi(data->token, data->fdout, data))
	{
		data->exit_status = 1;
		return (ft_free_token(data->token, data));
	}
	else if (data->token->type == S_QUOTES || data->token->type == D_QUOTES)
	{
		ft_putstr_fd("bash: ", data->fdout);
		ft_putstr_fd(data->token->str, data->fdout);
		ft_putstr_fd(": command not found\n", data->fdout);
		data->exit_status = 1;
	}
	ft_process_pipeline(data, ft_count_pipes(data->token));
	while (data->token->prev != NULL)
		data->token = data->token->prev;
	ft_free_token(data->token, data);
}

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
