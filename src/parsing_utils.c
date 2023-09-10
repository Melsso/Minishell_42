/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:18 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 14:13:47 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_tree	*create_node(enum e_token type, void *content, t_term *term)
{
	t_tree	*node;

	node = (t_tree *)my_malloc(&term->mem_lst, sizeof(t_tree));
	if (!node)
	{
		//handle malloc error
	}
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
		curr->l = create_node(TK_ARGS, NULL, term);
		*root = curr;
	}
	else
	{
		while (nb_pipes--)
		{
			curr = create_node(TK_PL, NULL, term);
			curr->l = create_node(TK_CMD, NULL, term);
			curr->l->l = create_node(TK_ARGS, NULL, term);
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
		tmp->r->l = create_node(TK_ARGS, NULL, term);
	}
}

static void	populate_tree(t_tree **root, char *input, t_term *term)
{
	t_tree	*tmp;
	ssize_t	i;
	char	**pipe_split;
	char	**cmd;

	pipe_split = ft_split(input , TK_PIPE, term);
	if (!pipe_split)
	{
		//handle malloc error
	}
	i = -1;
	tmp = *root;
	while (pipe_split[++i])
	{
		cmd = ft_split(pipe_split[i], TK_SPACE, term);
		if (!cmd)
		{
				//malloc error
		}
		if (tmp->type == TK_PL)
		{
			tmp->l->content = cmd[0];
			tmp->l->l->content = pipe_split[i];
			tmp = tmp->r;
		}
		else if (tmp->type == TK_CMD)
		{
			tmp->content = cmd[0];
			tmp->l->content = pipe_split[i];
		}
	}
		
}

void	init_s(t_term *term, char *input)
{
	ssize_t	i;
	t_tree	*root;

	i = -1;
	term->nb_pipes = 0;
	term->ast = NULL;
	root = NULL;
	while (input && input[++i])
	{
		if (input[i] == TK_PIPE)
			term->nb_pipes++;
	}
	term->pids = (pid_t *)my_malloc(&term->mem_lst, sizeof(pid_t) * (term->nb_pipes + 1));
	create_tree(term->nb_pipes, &root, term);
	populate_tree(&root, input, term);
	term->ast = root;
}
