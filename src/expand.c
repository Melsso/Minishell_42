/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:32:00 by smallem           #+#    #+#             */
/*   Updated: 2023/11/28 17:01:43 by smallem          ###   ########.fr       */
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
	if (!ft_isalpha(to_find[0]) && to_find[0] != '?' && to_find[0] != '_')
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
	mat[0] = (char *)my_malloc(&term->mem_lst, line_size + 1);
	mat[0][line_size] = 0;
	mat[1] = (char *)my_malloc(&term->mem_lst, line_size + 1);
	mat[1][line_size] = 0;
	return (mat);
}

int	skip_rd(char *str, int i)
{
	int	flag;

	i += 2;
	while (str[i] && is_space(str[i]))
		i++;
	flag = 0;
	while (str[i] && (!is_space(str[i]) || (is_space(str[i]) && flag % 2 == 1)))
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			flag++;
		i++;
	}
	i--;
	return (i);
}

int	skip_copy(char *str, char **mat, int *j, int i)
{
	int	flag;

	mat[1][(*j)] = '0';
	mat[0][(*j)++] = str[i++];
	mat[1][(*j)] = '0';
	mat[0][(*j)++] = str[i++];
	while (str[i] && is_space(str[i]))
	{
		mat[1][(*j)] = '0';
		mat[0][(*j)++] = str[i++];
	}
	flag = 0;
	while (str[i] && (!is_space(str[i]) || (is_space(str[i]) && flag % 2 == 1)))
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			flag++;
		mat[1][(*j)] = '0';
		mat[0][(*j)++] = str[i++];
	}
	return (i);
}

int	expand(t_term *term, t_cmd *cmd, char *str)
{
	int		i[3];
	t_fetch	*to_fetch;
	char	**mat;

	i[2] = -1;
	init_arr(i, 2);
	while (str[++i[2]])
	{
		if (str[i[2]] == TK_DQUOTE)
			i[1]++;
		else if (str[i[2]] == TK_SQUOTE && i[1] % 2 == 0)
			i[2] = skip_quote(str, i[2] + 1, str[i[2]]);
		else if (str[i[2]] == TK_LESS && str[i[2] + 1] == TK_LESS)
			i[2] = skip_rd(str, i[2]);
		else if (str[i[2]] == TK_DOLLAR)
			i[0]++;
	}
	to_fetch = fill_fetch(str, term, i[0]);
	mat = create_lines(str, to_fetch, i[0], term);
	if (!mat)
		return (0);
	fill_lines(str, mat, to_fetch);
	if (!redirect(cmd, mat, term))
		return (0);
	return (clean(term, cmd, mat));
}
