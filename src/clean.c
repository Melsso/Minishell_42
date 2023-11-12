/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:34:15 by smallem           #+#    #+#             */
/*   Updated: 2023/11/12 16:39:01 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	quote_ind(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			return (i);
		else
			i++;
	}
	return (-1);
}

static int	quote_lind(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		else
			i--;
	}
	return (-1);
}

static void	clean_cmd(t_tree *node, t_term *term)
{
	t_cmd	*cmd;
	int		i;
	int		len;
	int		j;
	int		fi;
	int		li;
	char	*line;

	cmd = (t_cmd *)node->content;
	if (!cmd)
		return ;
	i = -1;
	while (cmd->args[++i])
	{
		fi = quote_ind(cmd->args[i]);
		if (fi != -1)
		{
			li = quote_lind(cmd->args[i], cmd->args[i][fi]);
			line = (char *)my_malloc(&term->mem_lst, ft_strlen(cmd->args[i] - 2));
			j = 0;
			len = 0;
			while (cmd->args[i][j])
			{
				if (j != li && j != fi)
					line[len++] = cmd->args[i][j++];
				else
					j++;
			}
			line[len] = 0;
			cmd->args[i] = line;
		}
	}
}

static void	rec(t_tree *node, t_term *term)
{
	if (node->type == TK_PL)
	{
		rec(node->l, term);
		rec(node->r, term);
	}
	else
		clean_cmd(node, term);
}

void	clean(t_term *term)
{
	rec(term->ast, term);
}
