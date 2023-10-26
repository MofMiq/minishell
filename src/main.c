/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/10/26 19:05:10 by begarijo         ###   ########.fr       */
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
	if (data->token->type == S_QUOTES || data->token->type == D_QUOTES)
	{
		ft_putstr_fd("bash: ", data->fdout);
		ft_putstr_fd(data->token->str, data->fdout);
		ft_putstr_fd(": command not found\n", data->fdout);
		data->exit_status = 1;
		return (ft_free_token(data->token, data));
	}
	ft_process_pipeline(data, ft_count_pipes(data->token));
	while (data->token->prev != NULL)
		data->token = data->token->prev;
	ft_free_token(data->token, data);
}

// data->input = readline("\x1b[96mPutaShell> \x1b[0m");
void	ft_start_minishell(t_data *data)
{
	while (1)
	{
		ft_signal();
		data->input = readline("PutaShell> ");
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

// void	ft_leaks(void)
// {
// 	system("leaks -q minishell");
// }
// 	atexit(ft_leaks);

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	ft_display_banner();
	using_history();
	data = ft_init_data(env, argv);
	ft_start_minishell(data);
	ft_free_all(data);
	free(data);
	ft_display_banner_bye();
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

void	ft_display_banner_bye(void)
{
	ft_printf("%s                        888                                \n"\
	, BLUE);
	ft_printf("                        888                                \n");
	ft_printf("                        888                                \n");
	ft_printf("888  888        8888b.  88888b.   .d88b.  888d888  8888b.  \n");
	printf("888  888           \"88b 888 \"88b d88\"\"88b 888P\"       \"88b\
	\n");
	ft_printf("888  888       .d888888 888  888 888  888 888     .d888888 \n");
	ft_printf("Y88b 888       888  888 888  888 Y88..88P 888     888  888 \n");
	printf(" \"Y88888       \"Y888888 888  888  \"Y88P\"  888     \"Y888888\n");
	ft_printf("     888                                                   \n");
	ft_printf("Y8b d88P                                                   \n");
	ft_printf(" \"Y88P\"                                                  \n");
	ft_printf("            Y88b   d88P        d8888  .d88888b.            \n");
	ft_printf("             Y88b d88P        d88888 d88P\" \"Y88b         \n");
	ft_printf("              Y88o88P        d88P888 888     888           \n");
	ft_printf("               Y888P        d88P 888 888     888           \n");
	ft_printf("               d888b       d88P  888 888     888           \n");
	ft_printf("              d88888b     d88P   888 888     888           \n");
	ft_printf("             d88P Y88b   d8888888888 Y88b. .d88P           \n");
	ft_printf("           d88P   Y88b d88P     888  \"Y88888P\"            %s\n"\
	, END);
}
