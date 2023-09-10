/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:36:35 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 13:56:13 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

char	**f_all(char **set)
{
	int	i;

	i = 0;
	while (*(set + i))
	{
		free(*(set + i));
		i++;
	}
	free(set);
	return (NULL);
}

char	**create_set(char **set, char const *s, char c, t_term *term)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	while (*str)
	{
		while (*s == c)
			s++;
		str = (char *)s;
		while (*str && *str != c)
			str++;
		if (*str == c || str > s)
		{
			set[i] = ft_substr(s, 0, str - s, term);
			if (set[i] == NULL)
				return (f_all(set));
			s = str;
			i++;
		}
	}
	set[i] = NULL;
	return (set);
}

char	**ft_split(char const *s, char c, t_term *term)
{
	char	**set;

	set = my_malloc(&term->mem_lst, sizeof(char *) * (count_words(s, c) + 1));
	if (set == NULL)
		return (NULL);
	set = create_set(set, s, c, term);
	return (set);
}
