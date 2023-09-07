/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:40:42 by smallem           #+#    #+#             */
/*   Updated: 2023/04/02 17:12:42 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
	{
		tmp = malloc(1);
		if (tmp == NULL)
			return (NULL);
		*tmp = '\0';
		return (tmp);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	tmp = (char *)malloc(len + 1);
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, s + start, len + 1);
	return (tmp);
}
