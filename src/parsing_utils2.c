/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:21:51 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 14:14:05 by smallem          ###   ########.fr       */
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

// char    *check_str(char *input)
// {       
// }
