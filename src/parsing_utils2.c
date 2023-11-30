/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:59:11 by smallem           #+#    #+#             */
/*   Updated: 2023/11/28 18:36:29 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_invalid(char c, char n)
{
	if (c == ';' || c == '&' || c == '(' || c == ')' || c == ']'
		|| c == '{' || c == '}' || c == '!' || c == '%' || c == '#'
		|| c == '*' || c == '~')
		return (1);
	if (n && c == TK_PIPE && n == TK_PIPE)
		return (1);
	return (0);
}

int	check_syntax_2(t_term *term)
{
	int	i;

	i = 0;
	while (term->input[i])
	{
		i = skip_spaces(term->input, i);
		if (term->input[i])
			break ;
		if (term->input[i] == TK_SQUOTE || term->input[i] == TK_DQUOTE)
			i = skip_quote(term->input, i + 1, term->input[i]) + 1;
		else if (is_invalid(term->input[i], term->input[i + 1]))
		{
			term->ex_stat = 258;
			ft_putstr_fd("syntax error near unexpected token '", 2);
			if (term->input[i] == '!')
				ft_putstr_fd("newline", 2);
			else
				ft_putchar_fd(term->input[i], 2);
			ft_putstr_fd("'\n", 2);
			return (0);
		}
		else
			i++;
	}
	return (1);
}
