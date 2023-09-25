/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:42:21 by smallem           #+#    #+#             */
/*   Updated: 2023/09/25 18:11:09 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t mat_size(char *input, char sep)
{
	size_t	len;
	size_t	i;
	int		flag;
	char	c;

	len = 1;
	i = 0;
	flag = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			flag = 1;
			c = input[i++];
		}
		while (flag && input[i])
		{
			if (input[i] == c)
				flag = 0;
			i++;
		}
		if (input[i++] == sep && !flag)
			len++;
	}
	return (len);
}

char	**splt(char *input, t_term *term)
{
	char	**mat;
	char	*tmp;
	size_t	i;
	char	c;
	size_t	j;

	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (mat_size(input, '|') + 1));
	j = 0;
	i = -1;
	tmp = input;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			c = input[i++];
			while (input[i] && input[i] != c)
				i++;
			i++;
		}
		if (input[i] == '|')
		{
			mat[j++] = ft_substr(tmp, 0, input + i - tmp, term);
			tmp = input + i + 1;
		}
	}
	mat[j++] = ft_strdup(tmp, term);
	mat[j] = NULL;
	return (mat);
}

