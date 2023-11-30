/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:12:58 by smallem           #+#    #+#             */
/*   Updated: 2023/11/28 16:31:38 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*create_name(char *str, int j, int len, t_term *term)
{
	char	*name;
	char	c;

	name = (char *)my_malloc(&term->mem_lst, (len + 1));
	name[len] = 0;
	len = 0;
	while (str[j] && str[j] != TK_SPACE && str[j] != TK_GREATER
		&& str[j] != TK_LESS)
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

int	get_name(char *str, t_term *term, char **name, int flag)
{
	int		i;
	int		j;
	int		qflag;

	qflag = 0;
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	j = i;
	while (str[i] && !is_space(str[i]) && str[i] != TK_GREATER
		&& str[i] != TK_LESS)
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
		{
			i = skip_quote(str, i + 1, str[i]) + 1;
			qflag = 1;
		}
		else
			i++;
	}
	if (!qflag || flag == 4)
		*name = ft_substr(str, j, i - j, term);
	else
		*name = create_name(str, j, i - j - 2, term);
	return (i);
}

int	get_fname(char *str, t_term *term, int flag, t_cmd *cmd)
{
	int		i;
	char	*name;

	i = get_name(str, term, &name, flag);
	if (!ft_strlen(name))
		return (ft_putstr_fd("syntax error near unexpected token '", 2),
			ft_putchar_fd(*(str - 1), 2), ft_putstr_fd("'\n", 2), -1);
	if (flag == 1 || flag == 3)
	{
		if (open_outfiles(flag, name, cmd, term) == -1)
			return (-1);
	}
	else if (flag == 2 || flag == 4)
	{
		if (open_infiles(flag, name, cmd, term) == -1)
			return (-1);
	}
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (ft_error(name, ": Open function error", term, 1), -1);
	return (i);
}

static int	ft_msg(char **m, int i, t_term *term)
{
	term->ex_stat = 258;
	return (ft_putstr_fd("syntax error near unexpected token '", 2),
		ft_putchar_fd(m[0][i], 2), ft_putstr_fd("'\n", 2), 0);
}

int	test(int *i, char **m, t_term *term, t_cmd *cmd)
{
	char	*n_s;
	char	*n_t;
	int		len;
	int		flag;

	flag = !(m[0][*i] == TK_GREATER) + 1;
	n_s = ft_strjoin(ft_substr(m[0], 0, *i, term), " ", term);
	n_t = ft_strjoin(ft_substr(m[1], 0, *i, term), " ", term);
	if (m[0][++(*i)] == TK_GREATER || m[0][*i] == TK_LESS)
	{
		if (m[0][*i] != m[0][*i - 1])
			return (ft_msg(m, *i, term));
		(*i)++;
		flag += 2;
	}
	len = get_fname(&m[0][*i], term, flag, cmd) + *i;
	if (len - *i == -1)
		return (0);
	m[0] = ft_strjoin(n_s, ft_substr(m[0], len, ft_strlen(m[0]), term), term);
	m[1] = ft_strjoin(n_t, ft_substr(m[1], len, ft_strlen(m[1]), term), term);
	*i -= (flag > 2) + 1;
	return (1);
}
