/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:03:00 by smallem           #+#    #+#             */
/*   Updated: 2023/09/28 15:30:19 by smallem          ###   ########.fr       */
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
			init_s(term, input);
			add_history(term->input);
			// print_tree(term->ast);
			init_cmd(term);
		}
		else if (!input)
			break ;
	}
	free_lst(&term->mem_lst);
	printf(RESET);
}

int	main(int argc, char **argv, char **envp)
{
	// struct sigaction	sa;
	t_term	term;

	(void)argv;
	(void)envp;
	if (argc != 1)
		printf("No arguments allowed\n");
	main_loop(&term, envp);	
	return (0);	
}
