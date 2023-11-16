/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:44 by smallem           #+#    #+#             */
/*   Updated: 2023/11/16 18:44:53 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalnum(name[i]))
		return (printf("syntax error near unexpected token '%c'\n", name[i]), 0);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (printf("syntax error near unexpected token '%c'\n", name[i]), 0);
		i++;
	}
	return (1);
}

static int	get_fname(char *str, t_term *term, int flag, t_cmd *cmd)
{
	int		i;
	char	*name;
	int		j;

	i = 0;
	while (str[i] && str[i] == TK_SPACE)
		i++;
	j = i;
	while (str[i] && str[i] != TK_SPACE)
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			i = skip_quote(str, i, str[i]) + 1;
		else
			i++;
	}
	name = ft_substr(str, j, i - j, term);
	if (!check_name(name))
		return (-1);
	if (flag == 1)
		cmd->fd_out = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (flag == 2)
		cmd->fd_in = open(name, O_RDONLY);
	else if (flag == 3)
		cmd->fd_out = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);
	return (i);
}

int	redirect(t_cmd *cmd, char **mat, t_term *term)
{
	int		i;
	int		len;
	int		qflag;
	int		flag;
	char	*new_str;
	char	*new_tok;
	char	*tmp;

	i = 0;
	flag = 0;
	qflag = 0;
	while (mat[0][i])
	{
		if (mat[0][i] == TK_SQUOTE)
			qflag++;
		if (qflag % 2 == 0)
		{
			if ((mat[0][i] == TK_GREATER || mat[0][i] == TK_LESS) && mat[0][i] != mat[1][i])
			{
				if (mat[0][i] == TK_GREATER)
					flag = 1;
				else
					flag = 2;
				new_str = ft_substr(mat[0], 0, i, term);
				new_tok = ft_substr(mat[1], 0, i, term);
				new_str = ft_strjoin(new_str, " ", term);
				new_tok = ft_strjoin(new_tok, " ", term);
				i++;
				if (mat[0][i] == TK_GREATER || mat[0][i] == TK_LESS)
				{
					if (mat[0][i] != mat[0][i - 1])
						return (printf("syntax error near unexpected token '%c'\n", mat[0][i]), 0);
					i++;
					flag += 2;
				}
				len = get_fname(&mat[0][i], term, flag, cmd) + i;
				if (len - i == -1)
					return (0);
				tmp = ft_substr(mat[0], len, ft_strlen(mat[0]), term);
				mat[0] = ft_strjoin(new_str, tmp, term);
				tmp = ft_substr(mat[1], len, ft_strlen(mat[1]), term);
				mat[1] = ft_strjoin(new_tok, tmp, term);
				if (flag > 2)
					i -= 2;
				else
					i--;
			}
			else
				i++;
		}
		else
			i++;
		flag = 0;
	}
	return (1);
}
