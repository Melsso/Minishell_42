/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:42:21 by smallem           #+#    #+#             */
/*   Updated: 2023/11/28 12:56:32 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (is_space(str[i]))
		{
			i = skip_spaces(str, i);
			if (str[i])
				size++;
		}
		else if ((str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
			&& str_tok[i] == '0')
			i = skip_q(str, i + 1, str[i], str_tok) + 1;
		else
			i++;
	}
	return (size);
}

static	char	**init_all(t_term *term, t_cmd *cmd, int len, int *i)
{
	char	**mat;

	mat = (char **)my_malloc(&term->mem_lst, sizeof(char *)
			* (len + 2));
	cmd->args = (char **)my_malloc(&term->mem_lst, sizeof(char *)
			* (len + 2));
	mat[len + 1] = NULL;
	cmd->args[len + 1] = NULL;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	return (mat);
}

char	**splt_space(t_cmd *cmd, char *s, char *s_t, t_term *term)
{
	char	**mat;
	int		i[3];

	mat = init_all(term, cmd, m_size(s, s_t), i);
	while (s[i[1]])
	{
		while (is_space(s[i[1]]))
			i[1]++;
		i[2] = i[1];
		while (s[i[1]] && !is_space(s[i[1]]))
		{
			if ((s[i[1]] == TK_SQUOTE || s[i[1]] == TK_DQUOTE)
				&& s_t[i[1]] == '0')
				i[1] += skip_q(&s[i[1]], 1, s[i[1]], &s_t[i[1]]);
			i[1]++;
		}
		if (is_space(s[i[1]]) || i[1] > i[2])
		{
			cmd->args[i[0]] = ft_substr(&s[i[2]], 0, &s[i[1]] - &s[i[2]], term);
			mat[i[0]++] = ft_substr(&s_t[i[2]], 0, &s_t[i[1]]
					- &s_t[i[2]], term);
			i[2] = i[1];
		}
	}
	return (mat);
}
