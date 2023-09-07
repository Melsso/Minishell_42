/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:39:00 by smallem           #+#    #+#             */
/*   Updated: 2023/03/24 21:09:45 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s2 == NULL && s1 != NULL)
		return (ft_strdup(s1));
	tmp = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, s1, ft_strlen(s1) + 1);
	ft_strlcat(tmp, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (tmp);
}
