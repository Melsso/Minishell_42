/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:14:36 by smallem           #+#    #+#             */
/*   Updated: 2023/03/22 19:48:54 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*tmp;
	size_t		i;

	i = 0;
	tmp = (const char *)s;
	while (i < n)
	{
		if ((unsigned char)tmp[i] == (unsigned char)c)
			return ((unsigned char *)(tmp + i));
		i++;
	}
	return (NULL);
}
