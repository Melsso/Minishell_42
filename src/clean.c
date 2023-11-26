/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:34:15 by smallem           #+#    #+#             */
/*   Updated: 2023/11/26 17:02:54 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_len(char *arg, char *mat, int len)
{
	int	i;
	int	qflag;
	int	dqflag;

	i = 0;
	qflag = 0;
	dqflag = 0;
	len = 0;
	while (arg[i])
	{
		if (arg[i] == TK_SQUOTE && mat[i] == '0' && dqflag % 2 == 0)
			qflag++;
		else if (arg[i] == TK_DQUOTE && mat[i] == '0' && qflag % 2 == 0)
			dqflag++;
		if (arg[i] == TK_SQUOTE && mat[i] == '0' && dqflag % 2 == 0)
			i++;
		else if (arg[i] == TK_DQUOTE && mat[i] == '0' && qflag % 2 == 0)
			i++;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

static char	*new_line(char *arg, char *mat, int len, char *line)
{
	int		i;
	int		qflag;
	int		dqflag;

	i = 0;
	qflag = 0;
	dqflag = 0;
	len = 0;
	while (arg[i])
	{
		if (arg[i] == TK_SQUOTE && mat[i] == '0' && dqflag % 2 == 0)
			qflag++;
		else if (arg[i] == TK_DQUOTE && mat[i] == '0' && qflag % 2 == 0)
			dqflag++;
		if (arg[i] == TK_SQUOTE && mat[i] == '0' && dqflag % 2 == 0)
			i++;
		else if (arg[i] == TK_DQUOTE && mat[i] == '0' && qflag % 2 == 0)
			i++;
		else
			line[len++] = arg[i++];
	}
	return (line);
}

int	clean(t_term *term, t_cmd *cmd, char **mat)
{
	int		i;
	int		len;
	char	*line;

	mat = splt_space(cmd, mat[0], mat[1], term);
	i = 0;
	while (cmd->args[i])
	{
		len = count_len(cmd->args[i], mat[i], len);
		line = (char *)my_malloc(&term->mem_lst, (len + 1));
		line[len] = 0;
		cmd->args[i] = new_line(cmd->args[i], mat[i], len, line);
		i++;
	}
	return (1);
}
