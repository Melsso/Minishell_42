/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:03:00 by smallem           #+#    #+#             */
/*   Updated: 2023/11/19 17:56:59 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	main_loop(t_term *term, char **env)
{
	char	*input;

	term->env = copy_env(env, term);
	printf(GREEN);
	while (1)
	{
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
	t_term	term;

	(void)argv;
	(void)envp;
	ex_stat = 0;
	if (argc != 1)
		printf("No arguments allowed\n");
	// if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	// {
	// 	perror("");
	// 	ex_stat = errno;
	// 	exit(ex_stat);
	// }
	// if (signal(SIGINT, sigint_handler) == SIG_ERR)
	// {
	// 	perror("");
	// 	ex_stat = errno;
	// 	exit(ex_stat);
	// }
	// if (signal(SIGSTP, sigstp_handler) == SIG_ERR)
	// {
	// 	perror("");
	// 	ex_stat = errno;
	// 	exit(ex_stat);
	// }
	main_loop(&term, envp);	
	exit(0);
}
