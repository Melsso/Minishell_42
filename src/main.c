/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:03:00 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 14:16:22 by smallem          ###   ########.fr       */
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
			add_history(input);
			init_s(term, input);
			print_tree(term->ast);
		}
		else if (!input)
			break ;
	}
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
