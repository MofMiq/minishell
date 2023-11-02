/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begarijo <begarijo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:27 by marirodr          #+#    #+#             */
/*   Updated: 2023/11/02 19:10:19 by begarijo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*This function checks some errors, especially related to syntax, and we call
two other really important functions if the input is well-written: ft_init_parse
and ft_process_pipeline. Briefly, the first 'translates' the input and the later
checks for pipes or redirectios to change the default file descriptors.*/

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
/*This function is the one that keeps the program running indefinitely until
the user decides to close the shell, either executing the exit builtin or
with a signal.

As mentioned in previous comments, readline() is the function with which we
name our shell and the one that allow the user to input commands, which we
save in our main structure for future manipulation. We also use add_history()
to save all the previously written inputs.

Before we begin parsing the input, we check some few things that doesn't make
our shell work like the case the user don't close a quote or when the input
consist of all spaces. If everything is okey, we go to ft_check type :)*/

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
			{
				ft_putstr_fd("No has cerrao comillas chula\n", data->fdout);
				data->exit_status = 1;
			}
			else if (!ft_is_all_space(data->input, data))
				ft_check_type(data);
		}
		free(data->input);
	}
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

/*We begin out shell displaying a banner for fun :), initializing our main
data structure and calling using_history(). This is one of the funcion of
readline library, that are used when making a shell because is a more
advanced console line input manipulation than simply using scanf or gets.*/

int	main(int argc, char **argv, char **env)
{
	atexit(ft_leaks);
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
