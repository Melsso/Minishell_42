/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:13:58 by smallem           #+#    #+#             */
/*   Updated: 2023/11/23 16:50:37 by smallem          ###   ########.fr       */
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
			i = skip_quote(str, i + 1, TK_SQUOTE) + 1;
		else if (str[i] == TK_DOLLAR)
		{
			j = adv(str, i + 1);
			to_fetch[k].name = ft_substr(str, i, j - i, term);
			fill_fetch_2(term, &to_fetch[k++], i, j);
			i = j;
		}
		else
			i++;
	}
	return (to_fetch);
}
