/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:03:00 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 18:50:58 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	main_loop(t_term *term, char **env)
{
	char	*input;

	term->env = copy_env(env, term);
	while (1)
	{
		printf(GREEN);
		termios_echoback(false);
		if (isatty(fileno(stdin)))
			input = readline("~~> ");
		if (input && *input)
		{
			if (!init_s(term, input))
			{
				add_history(term->input);
				continue ;
			}
			add_history(term->input);
			execution(term);
		}
		else if (!input)
			break ;
	}
	free_lst(&term->mem_lst);
	printf(RESET);
}

int	main(int argc, char **argv, char **envp)
{
	t_term				term;

	(void)argv;
	(void)envp;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	term.ex_stat = 0;
	term.mem_lst = NULL;
	term.ast = NULL;
	if (argc != 1)
		return (ft_putstr_fd("No arguments allowed\n", 2), 0);
	main_loop(&term, envp);
	exit(term.ex_stat);
}
