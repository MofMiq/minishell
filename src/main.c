/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/09/26 18:11:16 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_check_type(t_data *data)
{	
	if ((ft_is_closed(data->input, '\'') % 2 != 0)
		|| (ft_is_closed(data->input, '\"') % 2 != 0))
		printf("No has cerrao comillas chula\n");
	else
	{
		ft_init_parse(data);
		if (ft_bad_redi(data->token))
			return (ft_free_token(data->token, data));
		else if (ft_is_redi(data->token))
			ft_what_redi(data);
		else if (data->token->type == BUILTIN)
			ft_do_builtins(data, data->token->str);
		else if (data->token->type == S_QUOTES || data->token->type == D_QUOTES)
			printf("bash: %s: command not found\n", data->token->str);
		else if (data->token->type != BUILTIN && data->args)
		{
			ft_launch_exec(data);
			printf("que quiereh\n");
		}
		ft_free_token(data->token, data);
	}
}

void	ft_start_minishell(t_data *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_handler);
	while (1)
	{
		data->input = readline("\x1b[96mPutaShell> \x1b[0m");
		if (data->input == NULL)
		{
			printf("Eres un cuadro, CHAO\n");
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			ft_check_type(data);
		}
		free(data->input); //para evitar leak vacio cuando solo pulsas enter
	}
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	atexit(ft_leaks);
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
