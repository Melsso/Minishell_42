/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:42:21 by smallem           #+#    #+#             */
/*   Updated: 2023/09/23 19:02:41 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t mat_size(char *input, char sep)
{
	size_t	len;
	size_t	i;
	int		flag;

	len = 1;
	i = 0;
	flag = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			flag = 1;
			i++;
		}
		while (flag && input[i])
		{
			if (input[i] == '"' || input[i] == '\'')
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
	size_t	len;
	char	**mat;
	char	*tmp;
	size_t	i;
	size_t	j = 0;
	int	flag;

	flag = 0;
	len = mat_size(input, '|');
	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (len + 1));
	i = 0;
	tmp = input;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			flag = 1;
			i++;
		}
		while (flag && input[i])
		{
			if (input[i] == '"' || input[i] == '\'')
				flag = 0;
			i++;
		}
		if (input[i] == '|' && !flag)
		{
			mat[j] = ft_substr(tmp, 0, input + i - tmp, term);
			tmp = input + i + 1;
			j++;
		}
		i++;
	}
	mat[j++] = ft_strdup(tmp, term);
	mat[j] = NULL;
	return (mat);
}

