/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:55:30 by smallem           #+#    #+#             */
/*   Updated: 2023/03/24 16:08:53 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*tmp;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	tmp = (char *)big;
	i = 0;
	while (i < len && *tmp)
	{
		if (*tmp == little[0] && i + ft_strlen(little) <= len)
		{
			if (!ft_strncmp(tmp, little, ft_strlen(little)))
				return (tmp);
		}
		i++;
		tmp++;
	}
	return (NULL);
}
