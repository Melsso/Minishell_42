/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:18 by smallem           #+#    #+#             */
/*   Updated: 2023/09/05 15:42:33 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_tree	*create_node(enum e_token type, void *content)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
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

static void	create_tree(ssize_t nb_pipes, t_tree **root)
{
	t_tree	*curr;
	t_tree	*tmp;

	if (!nb_pipes)
	{
		curr = create_node(TK_CMD, NULL);
		curr->l = create_node(TK_ARGS, NULL);
		*root = curr;
	}
	else
	{
		while (nb_pipes--)
		{
			curr = create_node(TK_PL, NULL);
			curr->l = create_node(TK_CMD, NULL);
			curr->l->l = create_node(TK_ARGS, NULL);
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
		tmp->r = create_node(TK_CMD, NULL);
		tmp->r->l = create_node(TK_ARGS, NULL);
	}
}

static void	populate_tree(t_tree **root, char *input)
{
	t_tree	*tmp;
	ssize_t	i;
	char	**pipe_split;
	char	**cmd;

	pipe_split = ft_split(input , TK_PIPE);
	if (!pipe_split)
	{
		//handle malloc error
	}
	i = -1;
	tmp = *root;
	while (pipe_split[++i])
	{
		cmd = ft_split(pipe_split[i], TK_SPACE);
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
	term->pids = (pid_t *)malloc(sizeof(pid_t) * (term->nb_pipes + 1));
	create_tree(term->nb_pipes, &root);
	populate_tree(&root, input);
	term->ast = root;
}
