/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:44 by smallem           #+#    #+#             */
/*   Updated: 2023/11/22 18:14:35 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*create_name(char *str, int j, int len, t_term *term)
{
	char	*name;
	char	c;
	
	name = (char *)my_malloc(&term->mem_lst, (len + 1));
	name[len] = 0;
	len = 0;
	while (str[j] && str[j] != TK_SPACE && str[j] != TK_GREATER && str[j] != TK_LESS)
	{
		if (str[j] == TK_SQUOTE || str[j] == TK_DQUOTE)
		{
			c = str[j];
			j++;
			while (str[j] && str[j] != c)
				name[len++] = str[j++];
			if (str[j] == c)
				j++;
		}
		else
			name[len++] = str[j++];
	}
	return (name);
}

static int	get_name(char *str, t_term *term, char **name)
{
	int		i;
	int		j;
	int		qflag;

	qflag = 0;
	i = 0;
	while (str[i] && str[i] == TK_SPACE)
		i++;
	j = i;
	while (str[i] && str[i] != TK_SPACE && str[i] != TK_GREATER && str[i] != TK_LESS)
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
		{
			i = skip_quote(str, i + 1, str[i]) + 1;
			qflag = 1;
		}
		else
			i++;
	}
	if (!qflag)
		*name = ft_substr(str, j, i - j, term);
	else
		*name = create_name(str, j, i - j - 2, term);
	return (i);
}

static int	get_fname(char *str, t_term *term, int flag, t_cmd *cmd)
{
	int		i;
	char	*name;

	i = get_name(str, term, &name);
	if (!ft_strlen(name))
		return (printf("syntax error near unexpected token '%c'\n", str[i]), -1);
	if (flag == 1 || flag == 3)
	{
		if (open_outfiles(flag, name, cmd) == -1)
			return (-1);
	}
	else if (flag == 2 || flag == 4)
	{
		if (open_infiles(flag, name, cmd) == -1)
			return (-1);
	}
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
	{
		ex_stat = 1;
		return (ft_putstr_fd(name, 1), ft_putstr_fd(": Open function error\n", 1), -1);
	}
	return (i);
}

static int test(int flag, int *i, char **mat, t_term *term, t_cmd *cmd)
{
	char *new_str;
	char *new_tok;
	int len;

	flag = !(mat[0][*i] == TK_GREATER) + 1;
	new_str = ft_strjoin(ft_substr(mat[0], 0, *i, term), " ", term);
	new_tok = ft_strjoin(ft_substr(mat[1], 0, *i, term), " ", term);
	(*i)++;
	if (mat[0][*i] == TK_GREATER || mat[0][*i] == TK_LESS)
	{
		if (mat[0][*i] != mat[0][*i - 1])
		{
			ex_stat = 258;
			return (printf("syntax error near unexpected token '%c'\n", mat[0][*i]), 0);
		}
		(*i)++;
		flag += 2;
	}
	len = get_fname(&mat[0][*i], term, flag, cmd) + *i;
	if (len - *i == -1)
		return (0);
	mat[0] = ft_strjoin(new_str, ft_substr(mat[0], len, ft_strlen(mat[0]), term), term);
	mat[1] = ft_strjoin(new_tok, ft_substr(mat[1], len, ft_strlen(mat[1]), term), term);
	*i -= (flag > 2) + 1;
	return (1);
}

int	redirect(t_cmd *cmd, char **mat, t_term *term)
{
	int		i;
	int		qflag;
	int		dqflag;
	int		flag;

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
			&& ((mat[0][i] == TK_GREATER || mat[0][i] == TK_LESS) && mat[0][i] != mat[1][i]))
		{
			if (!test(flag, &i, mat, term, cmd))
				return (0);
		}
		else
			i++;
	}
	return (1);
}
