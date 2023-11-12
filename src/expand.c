/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:32:00 by smallem           #+#    #+#             */
/*   Updated: 2023/11/12 19:27:14 by smallem          ###   ########.fr       */
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

// char	*ret_line(t_term *term, char *arg)
// {
// 	char	*tmp;

// 	tmp = ft_strchr(arg, '$');
// 	if (tmp)
// 	{
		
// 	}
// }

static void	expand_cmd(t_cmd *cmd, t_term *term)
{
	int		i;
	int		j;
	char	**to_find;
	char	*tmp;
	char	*t;
	char	*line;

	i = -1;
	line = NULL;
	while (cmd->args[++i])
	{
		tmp = ft_strchr(cmd->args[i], '$');
		if (tmp)
		{
			to_find = my_split(tmp, term);
			j = -1;
			while (to_find[++j])
			{
				t = to_find[j];
				if (to_find[j][1] == '?')
					line = ft_strjoin(line, ft_itoa(ex_stat, term), term);
				else if (to_find[j][1] != 0 && to_find[j][1] != TK_SQUOTE && to_find[j][1] != TK_DQUOTE)
					line = ft_strjoin(line, fetch_line(++t, term), term);
				else if (to_find[j][1] == 0)
					line = ft_strjoin(line, "$", term);
			}
			cmd->args[i] = line;
			line = NULL;
		}
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
