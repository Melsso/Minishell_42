/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:17:35 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 19:03:52 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/my_malloc.h"

static t_mem	*create_node(void *ptr, size_t size)
{
	t_mem	*tmp;

	tmp = (t_mem *)malloc(sizeof(t_mem));
	if (!tmp)
		return (NULL);
	tmp->ptr = ptr;
	tmp->size = size;
	tmp->next = NULL;
	return (tmp);
}

static void	add2lst(t_mem **lst, t_mem *node)
{
	t_mem	*tmp;

	tmp = *lst;
	if (!tmp)
		*lst = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	*my_malloc(t_mem **lst, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	add2lst(lst, create_node(ptr, size));
	return (ptr);
}

void	free_lst(t_mem **lst)
{
	t_mem	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->ptr);
		(*lst)->next = NULL;
		free(*lst);
		*lst = tmp;
	}
}
