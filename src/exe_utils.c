/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:39 by smallem           #+#    #+#             */
/*   Updated: 2023/11/09 15:56:10 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int exec_cmd(t_cmd *cmd, int tmp, t_term *term)
{
	dup2(tmp, STDIN_FILENO);
	close(tmp); // check
	if (cmd->fd_in > 2)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 2)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	if (execve(cmd->path, cmd->args, term->env) == -1)
	{
		ex_stat = errno;
		exit(errno);
	}
	return (1);
	// error
}

int exec_tree(t_term *term, t_tree *tree, int *tmp, int *fd)
{
	t_cmd	*cmd;

	if (tree->type == TK_PL)
	{
		exec_tree(term, tree->l, tmp, fd);
		exec_tree(term, tree->r, tmp, fd);
	}
	else if (tree->type == TK_CMD)
	{
		cmd = (t_cmd *) tree->content;
		if (cmd->index == term->nb_pipes) // check
		{
			if (!fork())
			{
				exec_cmd(cmd, *tmp, term);
				return (1);
				// error
			}
			close(*tmp);
			while (waitpid(-1, NULL, WUNTRACED) != -1)
				;
			*tmp = dup(STDIN_FILENO);
		}
		else
		{
			pipe(fd);
			if (!fork())
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				exec_cmd(cmd, *tmp, term);
				return (1);
				// error
			}
			close(fd[1]);
			close(*tmp);
			*tmp = fd[0];
		}
	}
	return (0);
}

int execution(t_term *term)
{
	int tmp;
	int fd[2];

// dprintf(0, "9lawi\n");
	tmp = dup(STDIN_FILENO);
	if (!term->ast)
		return 1;
	exec_tree(term, term->ast, &tmp, fd);
	close(tmp);
	return (0);
}
