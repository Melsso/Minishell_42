/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:32:00 by smallem           #+#    #+#             */
/*   Updated: 2023/11/23 17:43:47 by smallem          ###   ########.fr       */
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
		return (ft_strjoin(ft_itoa(term->ex_stat, term), &to_find[1], term));
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

char	**create_lines(char *str, t_fetch *to_fetch, int len, t_term *term)
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
			line_size = line_size - ft_strlen(to_fetch[k].name)
				+ ft_strlen(to_fetch[k].val);
			k++;
		}
	}
	mat[0] = (char *)my_malloc(&term->mem_lst, line_size);
	mat[0][line_size] = 0;
	mat[1] = (char *)my_malloc(&term->mem_lst, line_size);
	mat[1][line_size] = 0;
	return (mat);
}

static void	fill_lines_2(t_fetch *to_fetch, char **mat, int *j)
{
	int	n;

	n = 0;
	while (to_fetch->val[n])
	{
		if (to_fetch->val[n] == TK_SQUOTE || to_fetch->val[n] == TK_DQUOTE)
			mat[1][*j] = to_fetch->val[n];
		else if (to_fetch->val[n] == TK_GREATER || to_fetch->val[n] == TK_LESS)
			mat[1][*j] = to_fetch->val[n];
		else
			mat[1][*j] = '0';
		mat[0][(*j)++] = to_fetch->val[n++];
	}
}

void	fill_lines(char *str, char **mat, t_fetch *to_fetch)
{
	int	i;
	int	j;
	int	k;
	int	flag;

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
			fill_lines_2(&to_fetch[k], mat, &j);
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
	int		i;
	int		len;
	t_fetch	*to_fetch;
	char	**mat;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == TK_SQUOTE)
			i = skip_quote(str, i + 1, str[i]);
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
