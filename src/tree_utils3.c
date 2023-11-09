/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:42:21 by smallem           #+#    #+#             */
/*   Updated: 2023/11/09 13:39:50 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	mat_size(char *str)
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

	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (mat_size(str) + 2));
	j = 0;
	i = 0;
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			i = skip_quote(str, i + 1, str[i]) + 1;
		else if (str[i] == TK_PIPE)
		{
			mat[j++] = ft_substr(str, 0, i, term);
			str = str + i + 1;
			i = 0;
		}
		else
			i++;
	}
	mat[j++] = ft_strdup(str, term);
	mat[j] = NULL;
	return (mat);
}

static int	m_size(char *str)
{
	int	i;
	int	size;

	size = 0;
	i = skip_spaces(str, 0);
	while (str[i])
	{
		if (str[i] == TK_SPACE || str[i] == TK_TAB)
		{
			i = skip_spaces(str, i);
			if (str[i])
				size++;
		}
		else if(str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			i = skip_quote(str, i + 1, str[i]) + 1;
		else
			i++;
	}
	return (size);
}

char	**splt_space(char *str, t_term *term)
{
	char	**mat;
	char	*tmp;
	int		i;

	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (m_size(str) + 1));
	i = 0;
	tmp = str;
	while (*tmp)
	{
		while (*tmp == TK_SPACE || *tmp == TK_TAB)
			tmp++;
		str = tmp;
		while (*tmp && *tmp != TK_SPACE && *tmp != TK_TAB)
		{
			if (*tmp == TK_SQUOTE || *tmp == TK_DQUOTE)
				tmp += skip_quote(tmp, 1, *tmp);
			tmp++;
		}
		if (*tmp == TK_SPACE || *tmp == TK_TAB || tmp > str)
		{
			mat[i++] = ft_substr(str, 0, tmp - str, term);
			str = tmp;
		}
	}
	mat[i] = NULL;
	return (mat);
}

