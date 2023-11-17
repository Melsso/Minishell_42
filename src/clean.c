/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:34:15 by smallem           #+#    #+#             */
/*   Updated: 2023/11/17 14:31:04 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean(t_term *term, t_cmd *cmd, char **mat)
{
	int	i;
	int	len;
	int	j;
	char	*line;

	i = 0;
	while (cmd->args[i])
	{
		j = 0;
		len = 0;
		while (cmd->args[i][j])
		{
			if ((cmd->args[i][j] == TK_SQUOTE || cmd->args[i][j] == TK_DQUOTE) && mat[i][j] == '0')
				j++;
			else
			{
				j++;
				len++;
			}
		}
		line = (char *)my_malloc(&term->mem_lst, (len + 1));
		line[len] = 0;
		j = 0;
		len = 0;
		while (cmd->args[i][j])
		{
			if ((cmd->args[i][j] == TK_SQUOTE || cmd->args[i][j] == TK_DQUOTE) && mat[i][j] == '0')
				j++;
			else
				line[len++] = cmd->args[i][j++];
		}
		cmd->args[i] = line;
		i++;
	}
}
