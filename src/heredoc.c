/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:22:54 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 18:21:42 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_expand(char **delim, t_term *term)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	g_signo = 0;
	while (delim[0] && delim[0][i])
	{
		if (delim[0][i] == TK_SQUOTE || *delim[i] == TK_DQUOTE)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag)
	{
		delim[0] = ft_substr(*delim, 1, ft_strlen(*delim) - 2, term);
		return (flag);
	}
	else
		return (flag);
}

static char	*expand_line(char *line, t_term *term)
{
	int		i;
	int		j;
	char	**mat;

	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *) * 4);
	i = -1;
	while (line[++i])
	{
		if (line[i] == TK_DOLLAR)
		{
			j = i++;
			while (line[i] && !is_space(line[i]) && line[i] != TK_DOLLAR
				&& line[i] != TK_SQUOTE && line[i] != TK_DQUOTE)
				i++;
			mat[0] = ft_substr(line, j, i - j, term);
			mat[1] = ft_substr(line, 0, j, term);
			mat[2] = ft_substr(line, i, ft_strlen(line), term);
			mat[3] = fetch_line(mat[0] + 1, term);
			if (ft_strlen(mat[0]) == 1 && mat[0][0] == TK_DOLLAR)
				mat[3] = ft_strdup("$", term);
			line = ft_strjoin(ft_strjoin(mat[1], mat[3], term), mat[2], term);
			i = j + ft_strlen(mat[3]);
		}
	}
	return (line);
}

static int	ret(char *str, t_cmd *cmd)
{
	if (str)
		free(str);
	close(cmd->fd_in);
	signal(SIGINT, sighandler);
	if (g_signo == 2)
	{
		unlink("heredoc");
		cmd->heredoc = 0;
		return (-1);
	}
	return (1);
}

int	open_heredoc(char *delim, t_cmd *cmd, t_term *term)
{
	char	*str;
	int		flag;

	flag = check_expand(&delim, term);
	cmd->fd_in = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		if (g_signo)
			break ;
		str = readline(">");
		if (g_signo == 2)
			break ;
		if (!ft_strncmp(str, delim, ft_strlen(delim))
			&& !ft_strncmp(str, delim, ft_strlen(str)))
			break ;
		else
		{
			if (!flag && ft_strchr(str, TK_DOLLAR))
				str = expand_line(str, term);
			write(cmd->fd_in, ft_strjoin(str, "\n", term), ft_strlen(str) + 1);
			free(str);
			str = NULL;
		}
	}
	return (ret(str, cmd));
}
