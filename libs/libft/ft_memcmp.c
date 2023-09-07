/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:38:04 by smallem           #+#    #+#             */
/*   Updated: 2023/03/22 20:20:35 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*tmp;
	unsigned const char	*tmp1;

	tmp = (unsigned const char *)s1;
	tmp1 = (unsigned const char *)s2;
	while (n)
	{
		if (*tmp != *tmp1)
			return (*tmp - *tmp1);
		tmp++;
		tmp1++;
		n--;
	}
	return (0);
}
