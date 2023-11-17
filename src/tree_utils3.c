/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:42:21 by smallem           #+#    #+#             */
/*   Updated: 2023/11/17 14:24:15 by smallem          ###   ########.fr       */
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

static int	skip_q(char *str, int i, char c, char *str_tok)
{
	while (str[i])
	{
		if (str[i] != c || (str[i] == c && str_tok[i] == c))
			i++;
		else if (str[i] == c && str_tok[i] != c)
			return (i);
	}
	return (-1);
}

static int	m_size(char *str, char *str_tok)
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
		else if ((str[i] == TK_SQUOTE || str[i] == TK_DQUOTE) && str_tok[i] == '0')
			i = skip_q(str, i + 1, str[i], str_tok) + 1;
		else
			i++;
	}
	return (size);
}

char	**splt_space(t_cmd *cmd, char *str, char *str_tok, t_term *term)
{
	char	**mat;
	int		i;
	int		j;
	int		k;

	cmd->args = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (m_size(str, str_tok) + 1));
	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (m_size(str, str_tok) + 1));
	i = 0;
	j = 0;
	k = 0;
	while (str[j])
	{
		while (str[j] == TK_SPACE || str[j] == TK_TAB)
			j++;
		k = j;
		while (str[j] && str[j] != TK_SPACE && str[j] != TK_TAB)
		{
			if ((str[j] == TK_SQUOTE || str[j] == TK_DQUOTE) && str_tok[j] == '0')
				j += skip_q(&str[j], 1, str[j], &str_tok[j]);
			j++;
		}
		if (str[j] == TK_SPACE || str[j] == TK_TAB || j > k)
		{
			cmd->args[i] = ft_substr(&str[k], 0, &str[j] - &str[k], term);
			mat[i++] = ft_substr(&str_tok[k], 0, &str_tok[j] - &str_tok[k], term);
			k = j;
		}
	}
	cmd->args[i] = NULL;
	mat[i] = NULL;
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
