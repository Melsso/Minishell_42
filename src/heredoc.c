/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:22:54 by smallem           #+#    #+#             */
/*   Updated: 2023/11/25 15:50:45 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_heredoc(char *delim, t_cmd *cmd, t_term *term)
{
	char	*line;
	char	*buff;

	line = NULL;
	buff = NULL;
	cmd->heredoc = 1;
	cmd->fd_in = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (!ft_strncmp(line, delim, ft_strlen(delim))
			&& !ft_strncmp(line, delim, ft_strlen(line)))
			break ;
		else
		{
			line = ft_strjoin(line, "\n", term);
			write(cmd->fd_in, line, ft_strlen(line));
		}
	}
}
