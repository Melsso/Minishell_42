/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:18 by smallem           #+#    #+#             */
/*   Updated: 2023/09/28 15:23:16 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_tree	*create_node(enum e_token type, void *content, t_term *term)
{
	t_tree	*node;

	node = (t_tree *)my_malloc(&term->mem_lst, sizeof(t_tree));
	node->type = type;
	node->content = content;
	node->r = NULL;
	node->l = NULL;
	return (node);
}

static void	create_tree(ssize_t nb_pipes, t_tree **root, t_term *term)
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
		{
			curr = create_node(TK_PL, NULL, term);
			curr->l = create_node(TK_CMD, NULL, term);
			if (!(*root))
			{
				*root = curr;
				tmp = *root;
			}
			else
			{
				tmp->r = curr;
				tmp = tmp->r;
			}
		}	
		tmp->r = create_node(TK_CMD, NULL, term);
	}
}

static void	populate_tree(t_tree **root, t_term *term)
{
	t_tree	*tmp;
	ssize_t	i;
	char	**pipe_split;
	char	**cmd;

	pipe_split = splt(term->input, term);
	i = -1;
	tmp = *root;
	while (pipe_split[++i])
	{
		cmd = ft_split(pipe_split[i], TK_SPACE, term);
		if (tmp->type == TK_PL)
		{
			tmp->l->content = pipe_split[i];
			tmp = tmp->r;
		}
		else if (tmp->type == TK_CMD)
			tmp->content = pipe_split[i];
	}
}

static void	update_tree(t_term *term, t_tree **root)
{
	if (*root)
	{
		if ((*root)->type == TK_PL)
		{
			update_tree(term, &(*root)->l);
			update_tree(term, &(*root)->r);
		}
		else
			(*root)->content = build_cmd(term, root);
	}
}

void	init_s(t_term *term, char *input)
{
	ssize_t	i;
	t_tree	*root;

	i = -1;
	term->nb_pipes = 0;
	term->ast = NULL;
	term->input = NULL;
	root = NULL;
	if (!check_input(input, term))
		return ;
	term->nb_pipes = count_pipes(term);
	term->pids = (pid_t *)my_malloc(&term->mem_lst, sizeof(pid_t) * (term->nb_pipes + 1));
	create_tree(term->nb_pipes, &root, term);
	populate_tree(&root, term);
	term->ast = root;
	update_tree(term, &term->ast);
}
