/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:21:41 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 13:56:39 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, t_term *term)
{
	t_list	*tmp;

	tmp = my_malloc(&term->mem_lst, sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->content = content;
	tmp->next = NULL;
	return (tmp);
}
