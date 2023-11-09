/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:21:51 by smallem           #+#    #+#             */
/*   Updated: 2023/11/09 13:41:51 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_tree(t_tree* root) {
    if (root) {
        print_tree(root->l);
		t_cmd *cmd;
		cmd = (t_cmd *)root->content;
		if (cmd)
		{
			int	i = -1;
			printf("Args:\n");
			while (cmd->args[++i])
				printf("	-%s\n", cmd->args[i]);
        	printf("\nType: %d\nIndex: %d\nPath: %s\n fd_in: %d\n fd_out: %d\n\n", root->type, cmd->index, cmd->path, cmd->fd_in, cmd->fd_out);
		}
        print_tree(root->r);
    }
}

int	skip_spaces(char *str, int i)
{
	while (str[i] && (str[i] == TK_SPACE || str[i] == TK_TAB))
		i++;
	return (i);
}

int	count_pipes(t_term *term)
{
	int		count;
	int		i;
	char	c;

	count = 0;
	i = -1;
	while (term->input[++i])
	{
		if (term->input[i] == TK_PIPE)
			count++;
		if (term->input[i] == TK_SQUOTE || term->input[i] == TK_DQUOTE)
		{
			c = term->input[i++];
			while (term->input[i] && term->input[i] != c)
				i++;
		}
	}
	return (count);
}

int	check_quotes(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				continue;
			else
			{
				if (c == TK_SQUOTE)
					return (1);
				else
					return (2);
			}
		}
	}
	return (0);
}

int	skip_quote(char *str, int i, char c)
{
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	else
		return (-1);
}

int	check_flag(t_term *term)
{
	int	i;
	int	flag;

	i = skip_spaces(term->input, 0) - 1;
	while (term->input[++i])
	{
		if (term->input[i] == TK_PIPE)
		{
			i++;
			while (term->input[i] && (term->input[i] == TK_SPACE || term->input[i] == TK_NL))
				i++;
			if (!term->input[i])
				return (3);
			flag = check_quotes(term->input + i);
			if (!flag)
			{
				flag = skip_quote(term->input, i + 1, term->input[i]);
				if (flag != -1)
					i = flag;
				continue ;
			}
			else
				return (3 + flag);
		}
		else if (term->input[i] == TK_SQUOTE || term->input[i] == TK_DQUOTE)
		{
			flag = check_quotes(term->input + i);
			if (!flag)
				i = skip_quote(term->input, i + 1, term->input[i]);
			else
				return (flag);
		}
	}
	return (0);
}
