/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:39 by smallem           #+#    #+#             */
/*   Updated: 2023/09/05 16:38:44 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_term *term)
{
	if (execve() == -1)
	{
		//error
	}
}

void	init_cmd(t_term *term)
{
	ssize_t	i;

	i = -1;
	while (++i <= term->nb_pipes)
	{
		term->pids[i] = fork();
		if (term->pids[i] == -1)
		{
			//handle error
		}
		else if (!term->pids[i])
		{
			if (!term->nb_pipes)
				execute();
			else
				prep_pipes();
		}
		else if (i > 0)
			close_pipe();
	}
	i = -1;
	while (++i <= term->nb_pipes)
		waitpid(term->pids[i], NULL, 0);
}
