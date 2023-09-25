/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:21:51 by smallem           #+#    #+#             */
/*   Updated: 2023/09/25 12:37:31 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_tree(t_tree* root) {
    if (root) {
        print_tree(root->l);
        printf("Type: %d, Content: %s\n", root->type, root->content);
        print_tree(root->r);
    }
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
