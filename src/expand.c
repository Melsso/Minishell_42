/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:32:00 by smallem           #+#    #+#             */
/*   Updated: 2023/11/09 18:15:21 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fetch_line(char *to_find, t_term *term)
{
	int		i;
	char	*val;

	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], to_find, ft_strlen(to_find)))
		{
			val = ft_strdup(&term->env[i][ft_strlen(to_find) + 1], term);
			return (val);
		}
		else
			i++;
	}
	return (NULL);
}

static void	expand_cmd(t_cmd *cmd, t_term *term)
{
	int		i;
	char	*to_find;
	char	*line;

	i = 0;
	while (cmd->args[i])
	{
		to_find = ft_strchr(cmd->args[i], '$');
		if (to_find)
		{
			to_find++;
			if (*to_find == '?')
				cmd->args[i] = ft_itoa(ex_stat, term);
			else if (*to_find != 0)
			{
				line = fetch_line(to_find, term);
				if (line)
					cmd->args[i] = line;
				else
					cmd->args[i] = ft_strdup("", term);
			}
		}
		i++;
	}
}

void	expand(t_term *term, t_tree *node)
{
	t_cmd	*cmd;

	if (node->type == TK_PL)
	{
		expand(term, node->l);
		expand(term, node->r);
	}
	else if (node->type == TK_CMD)
	{
		cmd = (t_cmd *)node->content;
		expand_cmd(cmd, term);		
	}
}
