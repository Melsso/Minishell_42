/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:13:58 by smallem           #+#    #+#             */
/*   Updated: 2023/11/25 14:29:55 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	adv(char *str, int j)
{
	while (str[j] && str[j] != TK_SPACE && str[j] != TK_DOLLAR
		&& str[j] != TK_DQUOTE)
		j++;
	return (j);
}

static void	fill_fetch_2(t_term *term, t_fetch *to_fetch, int i, int j)
{
	to_fetch->start = i;
	if (ft_strlen(to_fetch->name) == 1)
		to_fetch->val = ft_strdup("$", term);
	else
		to_fetch->val = fetch_line(&to_fetch->name[1], term);
	to_fetch->end = j;
}

t_fetch	*fill_fetch(char *str, t_term *term, int len)
{
	t_fetch	*to_fetch;
	int		i[3];

	if (!len)
		return (NULL);
	to_fetch = (t_fetch *)my_malloc(&term->mem_lst, sizeof(t_fetch) * (len));
	i[0] = 0;
	i[2] = 0;
	while (str[i[0]])
	{
		if (str[i[0]] == TK_SQUOTE)
			i[0] = skip_quote(str, i[0] + 1, TK_SQUOTE) + 1;
		else if (str[i[0]] == TK_LESS && str[i[0] + 1] == TK_LESS)
			i[0] = skip_rd(str, i[0]) + 1;
		else if (str[i[0]] == TK_DOLLAR)
		{
			i[1] = adv(str, i[0] + 1);
			to_fetch[i[2]].name = ft_substr(str, i[0], i[1] - i[0], term);
			fill_fetch_2(term, &to_fetch[i[2]++], i[0], i[1]);
			i[0] = i[1];
		}
		else
			i[0]++;
	}
	return (to_fetch);
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
	int	i[4];

	init_arr(i, 4);
	while (str[i[0]])
	{
		if (str[i[0]] == TK_SQUOTE)
			i[2]++;
		else if (str[i[0]] == TK_LESS && str[i[0] + 1] == TK_LESS
			&& i[2] % 2 == 0)
		{
			i[0] = skip_copy(str, mat, &i[3], i[0]);
			continue ;
		}
		if (str[i[0]] == TK_DOLLAR && i[2] % 2 == 0)
		{
			fill_lines_2(&to_fetch[i[1]], mat, &i[3]);
			i[0] = to_fetch[i[1]++].end;
		}
		else
		{
			mat[1][i[3]] = '0';
			mat[0][i[3]++] = str[i[0]++];
		}
	}
}
