/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:32:00 by smallem           #+#    #+#             */
/*   Updated: 2023/11/13 19:46:11 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fetch_line(char *to_find, t_term *term)
{
	int		i;
	char	*val;
	char	**lst;

	i = 0;
	while (term->env[i])
	{
		lst = NULL;
		lst = ft_split(term->env[i], '=', term);
		if (!ft_strncmp(lst[0], to_find, ft_strlen(to_find)) && !ft_strncmp(lst[0], to_find, ft_strlen(lst[0])))
		{
			val = ft_strdup(&term->env[i][ft_strlen(to_find) + 1], term);
			return (val);
		}
		else
			i++;
	}
	return (ft_strdup("", term));
}

static int	is_in_quote(char *str, int pos)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == TK_SQUOTE)
		{
			while (str[i] && str[i] != TK_SQUOTE)
			{
				if (i == pos)
					return (1);
				i++;
			}
		}
		else if (str[i] == TK_DQUOTE)
		{
			while (str[i] && str[i] != TK_DQUOTE)
			{
				if (i == pos)
					return (2);
				i++;
			}
		}
		else
			i++;
	}
	return (0);
}
static void	expand_cmd(t_cmd *cmd, t_term *term)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*tmp;
	char	*name;
	char	*line;

	i = -1;
	while (cmd->args[++i])
	{
		tmp = cmd->args[i];
		j = 0;
		line = NULL;
		while (tmp[j])
		{
			if (tmp[j] == TK_SQUOTE)
			{
				// printf("--%s--\n", tmp);
				j = skip_quote(tmp, j, TK_SQUOTE) + 1;
				// printf("--%s--\n", tmp);
			}
			else
			{
				if (tmp[j] == TK_DOLLAR)
				{
					k = j;
					while (tmp[k] && tmp[k] != TK_SPACE && tmp[k] != TK_SQUOTE && tmp[k] != TK_DQUOTE)
						k++;
					name = ft_substr(tmp, j + 1, k - j - 1, term);
					line = fetch_line(name, term);
					len = ft_strlen(line) + j;
					line = ft_strjoin(ft_substr(tmp, 0, j, term), line, term);
					j = len;
					line = ft_strjoin(line, ft_substr(tmp, k, ft_strlen(tmp), term), term);
					tmp = line;
				}
				else
					j++;
			}
		}
		cmd->args[i] = tmp;
	}
}

/// above function needs ot be tested further
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
