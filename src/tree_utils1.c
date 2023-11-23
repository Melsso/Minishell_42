/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:30:04 by smallem           #+#    #+#             */
/*   Updated: 2023/11/23 17:07:36 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*create_node(enum e_token type, void *content, t_term *term)
{
	t_tree	*node;

	node = (t_tree *)my_malloc(&term->mem_lst, sizeof(t_tree));
	node->type = type;
	node->content = content;
	node->r = NULL;
	node->l = NULL;
	return (node);
}

static void	iter(t_term *term, t_tree **root, t_tree **tmp, t_tree **curr)
{
	(*curr) = create_node(TK_PL, NULL, term);
	(*curr)->l = create_node(TK_CMD, NULL, term);
	if (!(*root))
	{
		*root = *curr;
		*tmp = *root;
	}
	else
	{
		(*tmp)->r = *curr;
		*tmp = (*tmp)->r;
	}
}

void	create_tree(ssize_t nb_pipes, t_tree **root, t_term *term)
{
	t_tree	*curr;
	t_tree	*tmp;

	if (!nb_pipes)
	{
		curr = create_node(TK_CMD, NULL, term);
		*root = curr;
	}
	else
	{
		while (nb_pipes--)
			iter(term, root, &tmp, &curr);
		tmp->r = create_node(TK_CMD, NULL, term);
	}
}
