/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:39 by smallem           #+#    #+#             */
/*   Updated: 2023/09/28 15:53:46 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_tree *node, char **env)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)node->content;
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	if (execve(cmd->path, cmd->args, env) == -1)
	{
		//error
	}
}
// static void prep_pipe(t_term *term)
// {
	
// }

void	init_cmd(t_term *term)
{
	int	i;
	t_tree	*curr;

	i = -1;
	curr = term->ast;
	while (curr)
	{
		term->pids[++i] = fork();	
		if (!term->pids[i])
		{
			if (curr->type == TK_PL)
				execute(curr->l, term->env);
			else
				execute(curr, term->env);
		}
		else
			curr = curr->r;
	}
	i = -1;
	while (++i <= term->nb_pipes)
		waitpid(term->pids[i], NULL, 0);
}
