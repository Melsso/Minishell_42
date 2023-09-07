/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:18:44 by smallem           #+#    #+#             */
/*   Updated: 2023/03/28 14:44:09 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char			*tmp;

	tmp = (char *)malloc(ft_strlen(str) + 1);
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, str, ft_strlen(str) + 1);
	return (tmp);
}
