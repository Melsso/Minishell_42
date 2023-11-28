/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:44 by smallem           #+#    #+#             */
/*   Updated: 2023/11/28 14:26:25 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_outfiles(int flag, char *name, t_cmd *cmd, t_term *term)
{
	if (flag == 1 || flag == 3)
	{
		if (access(name, F_OK) == 0)
		{
			if (access(name, W_OK) == 0)
			{
				if (flag == 1)
					cmd->fd_out = open(name, O_WRONLY | O_TRUNC, 0644);
				else if (flag == 3)
					cmd->fd_out = open(name, O_WRONLY | O_APPEND, 0644);
			}
			else
				return (ft_error(name, ": Permission denied", term, 1), -1);
		}
		else
			cmd->fd_out = open(name, O_WRONLY | O_CREAT, 0644);
	}
	return (1);
}

int	open_infiles(int flag, char *name, t_cmd *cmd, t_term *term)
{
	if (flag == 2)
	{
		if (access(name, F_OK) == 0)
		{
			if (access(name, R_OK) == 0)
				cmd->fd_in = open(name, O_RDONLY);
			else
				return (ft_error(name, ": Permission denied", term, 1), -1);
		}
		else
			return (ft_error(name, ": No such file or directory", term, 1), -1);
	}
	else if (flag == 4)
		open_heredoc(name, cmd, term);
	return (1);
}

int	redirect(t_cmd *cmd, char **mat, t_term *term)
{
	int		i;
	int		qflag;
	int		dqflag;

	i = 0;
	qflag = 0;
	dqflag = 0;
	while (mat[0][i])
	{
		if (mat[0][i] == TK_SQUOTE && dqflag % 2 == 0)
			qflag++;
		else if (mat[0][i] == TK_DQUOTE && qflag % 2 == 0)
			dqflag++;
		if (qflag % 2 == 0 && dqflag % 2 == 0
			&& ((mat[0][i] == TK_GREATER || mat[0][i] == TK_LESS)
			&& mat[0][i] != mat[1][i]))
		{
			if (!test(&i, mat, term, cmd))
				return (0);
		}
		else
			i++;
	}
	return (1);
}
