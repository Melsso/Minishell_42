/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:32:00 by smallem           #+#    #+#             */
/*   Updated: 2023/11/17 14:24:21 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fetch_line(char *to_find, t_term *term)
{
	int		i;
	char	*val;
	char	**lst;

	i = 0;
	if (to_find[0] == TK_QST)
		return (ft_strjoin(ft_itoa(ex_stat, term), &to_find[1], term));
	if (ft_isdigit(to_find[0]))
		return (ft_strdup(&to_find[1], term));
	while (term->env[i])
	{
		lst = ft_split(term->env[i], '=', term);
		if (!ft_strncmp(lst[0], to_find, ft_strlen(to_find))
			&& !ft_strncmp(lst[0], to_find, ft_strlen(lst[0])))
		{
			val = ft_strdup(&term->env[i][ft_strlen(to_find) + 1], term);
			return (val);
		}
		else
			i++;
	}
	return (ft_strdup("", term));
}

static t_fetch	*fill_fetch(char *str, t_term *term, int len)
{
	t_fetch	*to_fetch;
	int		i;
	int		k;
	int		j;

	if (!len)
		return (NULL);
	to_fetch = (t_fetch *)my_malloc(&term->mem_lst, sizeof(t_fetch) * (len));
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == TK_SQUOTE)
			i = skip_quote(&str[i], i, TK_SQUOTE);
		else if (str[i] == TK_DOLLAR)
		{
			j = i + 1;
			while (str[j] && str[j] != TK_SPACE && str[j] != TK_DOLLAR && str[j] != TK_DQUOTE)
				j++;
			to_fetch[k].name = ft_substr(str, i, j - i, term);
			to_fetch[k].start = i;
			if (ft_strlen(to_fetch[k].name) == 1)
				to_fetch[k].val = ft_strdup("$", term);
			else
				to_fetch[k].val = fetch_line(&to_fetch[k].name[1], term);
			to_fetch[k++].end = j;
			i = j;
		}
		else
			i++;
	}
	return (to_fetch);
}

static char	**create_lines(char *str, t_fetch *to_fetch, int len, t_term *term)
{
	char	**mat;
	int		k;
	int		line_size;

	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *) * 3);
	mat[2] = NULL;
	line_size = ft_strlen(str);
	k = 0;
	if (to_fetch)
	{
		while (k < len)
		{
			// if (!to_fetch[k].valid_name)
			// 	return (NULL);
			line_size = line_size - ft_strlen(to_fetch[k].name) + ft_strlen(to_fetch[k].val);
			k++;
		}
	}
	mat[0] = (char *)my_malloc(&term->mem_lst, line_size);
	mat[0][line_size] = 0;
	mat[1] = (char *)my_malloc(&term->mem_lst, line_size);
	mat[1][line_size] = 0;
	return (mat);
}

static void	fill_lines(char *str, char **mat, t_fetch *to_fetch)
{
	int	i;
	int	j;
	int	k;
	int	n;
	int	flag;

	n = 0;
	i = 0;
	k = 0;
	j = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == TK_SQUOTE)
			flag++;
		if (str[i] == TK_DOLLAR && flag % 2 == 0)
		{
			n = 0;
			while (to_fetch[k].val[n])
			{
				if (to_fetch[k].val[n] == TK_SQUOTE || to_fetch[k].val[n] == TK_DQUOTE)
					mat[1][j] = to_fetch[k].val[n];
				else if (to_fetch[k].val[n] == TK_GREATER || to_fetch[k].val[n] == TK_LESS)
					mat[1][j] = to_fetch[k].val[n];
				else
					mat[1][j] = '0';
				mat[0][j++] = to_fetch[k].val[n++];
			}
			i = to_fetch[k++].end;
		}
		else
		{
			mat[1][j] = '0';
			mat[0][j++] = str[i++];
		}
	}
}

int	expand(t_term *term, t_cmd *cmd, char *str)
{
	int	i;
	int		len;
	t_fetch	*to_fetch;
	char **mat;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == TK_SQUOTE)
			i = skip_quote(str, i + 1, str[i]) + 1;
		else if (str[i] == TK_DOLLAR)
			len++;
		i++;
	}
	to_fetch = fill_fetch(str, term, len);
	mat = create_lines(str, to_fetch, len, term);
	if (!mat)
		return (0);
	fill_lines(str, mat, to_fetch);
	if (!redirect(cmd, mat, term))
		return (0);
	mat = splt_space(cmd, mat[0], mat[1], term);
	clean(term, cmd, mat);
	return (1);
}
