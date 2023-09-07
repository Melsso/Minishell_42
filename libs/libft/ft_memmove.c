/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:51:33 by smallem           #+#    #+#             */
/*   Updated: 2023/03/24 15:38:42 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	int		i;

	d = (char *)dest;
	s = (char *)src;
	if (d == s || n == 0)
		return (dest);
	if (d > s && d - s < (int)n)
	{
		i = n;
		while (--i >= 0)
			d[i] = s[i];
		return (dest);
	}
	if (s > d && s - d < (int)n)
	{
		i = -1;
		while (++i < (int)n)
			d[i] = s[i];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
