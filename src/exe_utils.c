/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:39 by smallem           #+#    #+#             */
/*   Updated: 2023/11/25 17:28:25 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_tree(t_term *term, t_tree *tree, int *tmp, int *fd)
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
		if (cmd->index == term->nb_pipes)
		{
			if (is_builtin(cmd))
				exe_builtins(cmd, term, 0);
			else
			{
				if (!fork())
				{
					exec_cmd(cmd, *tmp, term);
					return (1);
				}
				close(*tmp);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;
				*tmp = dup(STDIN_FILENO);
			}
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
			}
			close(fd[1]);
			close(*tmp);
			*tmp = fd[0];
		}
	}
	return (0);
}

static void	iter_tree(t_tree *tree)
{
	t_cmd	*cmd;

	if (tree->type == TK_PL)
	{
		iter_tree(tree->l);
		iter_tree(tree->r);
	}
	else if (tree->type == TK_CMD)
	{
		cmd = (t_cmd *)tree->content;
		if (cmd->heredoc)
			unlink("heredoc");
	}
}

int	execution(t_term *term)
{
	int	tmp;
	int	fd[2];

	tmp = dup(STDIN_FILENO);
	if (!term->ast)
		return (1);
	exec_tree(term, term->ast, &tmp, fd);
	close(tmp);
	iter_tree(term->ast);
	return (0);
}
