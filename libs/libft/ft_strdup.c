/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:18:44 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 13:56:22 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str, t_term *term)
{
	char			*tmp;

	tmp = my_malloc(&term->mem_lst, ft_strlen(str) + 1);
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	return (tmp);
}
