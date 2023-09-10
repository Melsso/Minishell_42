/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:57:24 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 13:56:04 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_inset(char const s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set, t_term *term)
{
	char	*tmp;
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	while (s1[i] && is_inset(s1[i], set))
		i++;
	j = ft_strlen(s1);
	while (j > i && is_inset(s1[j - 1], set))
		j--;
	tmp = my_malloc(&term->mem_lst, j - i + 1);
	if (tmp == NULL)
		return (NULL);
	k = 0;
	while (i < j)
	{
		tmp[k] = s1[i];
		i++;
		k++;
	}
	tmp[k] = '\0';
	return (tmp);
}
