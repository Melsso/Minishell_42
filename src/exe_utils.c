/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:39 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 19:18:01 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cmd_null(t_term *term, t_cmd *cmd, int *tmp)
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
		while (waitpid(-1, &term->ex_stat, WUNTRACED) != -1)
			;
		if (((*(int *)&(term->ex_stat)) & 0177) == 0)
			term->ex_stat = ((*(int *)&(term->ex_stat)) >> 8) & 0x000000ff;
		*tmp = dup(STDIN_FILENO);
	}
	return (1);
}

static int	cmd_pipe(t_term *term, t_cmd *cmd, int *tmp)
{
	int	fd[2];

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
	return (1);
}

int	exec_tree(t_term *term, t_tree *tree, int *tmp)
{
	t_cmd	*cmd;

	if (tree->type == TK_PL)
	{
		exec_tree(term, tree->l, tmp);
		exec_tree(term, tree->r, tmp);
	}
	else if (tree->type == TK_CMD)
	{
		cmd = (t_cmd *) tree->content;
		if (cmd->index == term->nb_pipes)
			(void) cmd_null(term, cmd, tmp);
		else
			(void) cmd_pipe(term, cmd, tmp);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
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

	signal(SIGINT, sighp);
	tmp = dup(STDIN_FILENO);
	if (!term->ast)
		return (1);
	exec_tree(term, term->ast, &tmp);
	close(tmp);
	iter_tree(term->ast);
	signal(SIGINT, sighandler);
	return (0);
}
