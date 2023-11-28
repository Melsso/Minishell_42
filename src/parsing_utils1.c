/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:21:51 by smallem           #+#    #+#             */
/*   Updated: 2023/11/28 12:55:28 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] && (str[i] == TK_SPACE || str[i] == TK_TAB
			|| str[i] == TK_NL))
		i++;
	return (i);
}

int	count_pipes(t_term *term)
{
	int		count;
	int		i;
	char	c;

	count = 0;
	i = -1;
	while (term->input[++i])
	{
		if (term->input[i] == TK_PIPE)
			count++;
		if (term->input[i] == TK_SQUOTE || term->input[i] == TK_DQUOTE)
		{
			c = term->input[i++];
			while (term->input[i] && term->input[i] != c)
				i++;
		}
	}
	return (count);
}

int	check_quotes(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == TK_SQUOTE || str[i] == TK_DQUOTE)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				continue ;
			else
			{
				if (c == TK_SQUOTE)
					return (1);
				else
					return (2);
			}
		}
	}
	return (0);
}

static int	check_flag_pipe(t_term *term, int *i, int *flag)
{
	(*i)++;
	while (term->input[*i] && is_space(term->input[*i]))
		(*i)++;
	if (!term->input[*i])
	{
		*flag = 0;
		return (3);
	}
	*flag = check_quotes(term->input + *i);
	if (!*flag)
	{
		*flag = skip_quote(term->input, *i + 1, term->input[*i]);
		if (*flag != -1)
			*i = *flag;
		return (-1);
	}
	else
		return (3 + *flag);
}

int	check_flag(t_term *term)
{
	int	i;
	int	flag;
	int	ret;

	i = skip_spaces(term->input, 0) - 1;
	while (term->input[++i])
	{
		if (term->input[i] == TK_PIPE)
		{
			ret = check_flag_pipe(term, &i, &flag);
			if (ret >= 3)
				return (3 + flag);
			else if (ret == -1)
				continue ;
		}
		else if (term->input[i] == TK_SQUOTE || term->input[i] == TK_DQUOTE)
		{
			flag = check_quotes(term->input + i);
			if (!flag)
				i = skip_quote(term->input, i + 1, term->input[i]);
			else
				return (flag);
		}
	}
	return (0);
}
