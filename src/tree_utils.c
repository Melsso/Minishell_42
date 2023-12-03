/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:18 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 12:18:33 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*build_cmd(t_term *term, t_tree **node, int *ind)
{
	t_cmd	*cmd;
	char	*str;

	cmd = (t_cmd *)my_malloc(&term->mem_lst, sizeof(t_cmd));
	if ((*node)->content)
	{
		str = (char *)(*node)->content;
		cmd->fd_in = 0;
		cmd->fd_out = 1;
		cmd->heredoc = 0;
		cmd->index = *ind;
		if (!expand(term, cmd, str))
			return (NULL);
		if (!check_cmd(cmd, term))
			return (NULL);
		return (cmd);
	}
	return (NULL);
}

void	populate_tree(t_tree **root, t_term *term)
{
	t_tree	*tmp;
	ssize_t	i;
	char	**pipe_split;

	pipe_split = splt(term->input, term);
	i = -1;
	tmp = *root;
	while (pipe_split[++i])
	{
		if (tmp->type == TK_PL)
		{
			tmp->l->content = pipe_split[i];
			tmp = tmp->r;
		}
		else if (tmp->type == TK_CMD)
			tmp->content = pipe_split[i];
	}
}

void	update_tree(t_term *term, t_tree **root, int *i)
{
	if (*root)
	{
		if ((*root)->type == TK_PL)
		{
			update_tree(term, &(*root)->l, i);
			update_tree(term, &(*root)->r, i);
		}
		else
		{
			(*root)->content = build_cmd(term, root, i);
			if ((*root)->content == NULL)
			{
				(*root)->err = 1;
				return ;
			}
			else
				(*root)->err = 0;
			(*i)++;
		}
	}
}

static int	iter(t_tree *root)
{
	t_tree	*node;

	node = root;
	while (node)
	{
		if (node->type == TK_PL)
		{
			if (node->l && node->l->err)
				return (0);
			node = node->r;
		}
		else if (node->type == TK_CMD)
		{
			if (node->err)
				return (0);
			else
				return (1);
		}
	}
	return (1);
}

int	init_s(t_term *term, char *input)
{
	int		i;
	t_tree	*root;

	i = 0;
	term->nb_pipes = 0;
	term->ast = NULL;
	term->input = NULL;
	root = NULL;
	if (!check_input(input, term))
		return (0);
	term->nb_pipes = count_pipes(term);
	create_tree(term->nb_pipes, &root, term);
	populate_tree(&root, term);
	term->ast = root;
	update_tree(term, &term->ast, &i);
	if (!iter(term->ast))
		term->ast = NULL;
	return (1);
}
