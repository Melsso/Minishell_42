/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:22:54 by smallem           #+#    #+#             */
/*   Updated: 2023/11/25 17:24:25 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_expand(char **delim, t_term *term)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*delim[i])
	{
		if (*delim[i] == TK_SQUOTE || *delim[i] == TK_DQUOTE)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag)
	{
		*delim = ft_substr(*delim, 1, ft_strlen(*delim) - 2, term);
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
			while (line[i] && !is_space(line[i]) && line[i] != TK_DOLLAR)
				i++;
			mat[0] = ft_substr(line, j, i - j, term);
			mat[1] = ft_substr(line, 0, j, term);
			mat[2] = ft_substr(line, i, ft_strlen(line), term);
			if (ft_strlen(mat[0]) == 1 && mat[0][0] == TK_DOLLAR)
				mat[3] = ft_strdup("$", term);
			else
				mat[3] = fetch_line(mat[0] + 1, term);
			line = ft_strjoin(ft_strjoin(mat[1], mat[3], term), mat[2], term);
			i = j + ft_strlen(mat[3]);
		}
	}
	return (line);
}

void	open_heredoc(char *delim, t_cmd *cmd, t_term *term)
{
	char	*str;
	int		flag;

	flag = check_expand(&delim, term);
	cmd->heredoc = 1;
	cmd->fd_in = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		str = readline(">");
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
	if (str)
		free(str);
	close(cmd->fd_in);
	cmd->fd_in = open("heredoc", O_RDONLY, 0644);
}
