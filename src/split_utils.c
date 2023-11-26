/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:52:44 by smallem           #+#    #+#             */
/*   Updated: 2023/11/26 18:51:10 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	m_siz(char *str)
{
	int		i;
	int		size;

	size = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			i = skip_quote(str, i + 1, str[i]);
		else if (str[i] == TK_PIPE)
			size++;
	}
	return (size);
}

char	**splt(char *str, t_term *term)
{
	char	**mat;
	int		i;
	int		j;

	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (m_siz(str) + 2));
	j = 0;
	i = -1;
	while (str[++i])
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			i = skip_quote(str, i + 1, str[i]);
		else if (str[i] == TK_PIPE)
		{
			mat[j++] = ft_substr(str, 0, i, term);
			str = str + i + 1;
			i = 0;
		}
	}
	mat[j++] = ft_strdup(str, term);
	mat[j] = NULL;
	return (mat);
}

static int	count(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (*str == TK_DOLLAR)
			len++;
		str++;
	}
	return (len);
}

char	**my_split(char *str, t_term *term)
{
	char	**arr;
	char	*tmp;
	int		i;

	i = 0;
	arr = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (count(str) + 1));
	tmp = str;
	while (*tmp)
	{
		if (*tmp == TK_DOLLAR)
		{
			str = tmp;
			tmp++;
			while (*tmp && *tmp != TK_DOLLAR)
				tmp++;
			arr[i] = ft_substr(str, 0, tmp - str, term);
			i++;
		}
		else
			tmp++;
	}
	arr[i] = NULL;
	return (arr);
}
