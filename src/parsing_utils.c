/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:54:27 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 18:25:53 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_msg(int flag, t_term *term)
{
	if (flag == 1)
		return (ft_strdup("quote>", term));
	else if (flag == 2)
		return (ft_strdup("dquote>", term));
	else if (flag == 3)
		return (ft_strdup("pipe>", term));
	else if (flag == 4)
		return (ft_strdup("pipe quote>", term));
	else if (flag == 5)
		return (ft_strdup("pipe dquote>", term));
	else
		return (NULL);
}

static void	read_more(int flag, t_term *term)
{
	char	*tmp;
	char	*line;

	flag = check_flag(term);
	while (flag)
	{
		tmp = NULL;
		tmp = get_msg(flag, term);
		term->input = ft_strjoin(term->input, "\n", term);
		line = readline(tmp);
		term->input = ft_strjoin(term->input, line, term);
		free(line);
		line = NULL;
		flag = check_flag(term);
	}
	return ;
}

static int	check_syntax(t_term *term, int i)
{
	i = skip_spaces(term->input, 0);
	if (!term->input[i])
		return (0);
	if (term->input[i] == TK_PIPE || term->input[i] == '&'
		|| term->input[i] == ';' || (term->input[i] == TK_PIPE
			&& term->input[i + 1] && term->input[i + 1] == TK_PIPE))
	{
		term->ex_stat = 258;
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putchar_fd(term->input[i], 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	else if (!ft_strncmp(&term->input[i], "<<", ft_strlen("<<"))
		|| !ft_strncmp(&term->input[i], ">>", ft_strlen(">>"))
		|| term->input[i] == TK_GREATER
		|| term->input[i] == TK_LESS)
	{
		i = skip_spaces(term->input, i + 1);
		if (!term->input[i])
			return (ft_error("syntax error near unexpected token 'newline'\n",
					NULL, term, 1), 0);
	}
	return (1);
}

int	check_input(char *input, t_term *term)
{
	int	i;

	term->input = NULL;
	term->input = ft_strdup(input, term);
	free(input);
	i = 0;
	if (!check_syntax(term, i))
		return (0);
	read_more(0, term);
	if (!check_syntax(term, i))
		return (0);
	return (check_syntax_2(term));
}

int	skip_quote(char *str, int i, char c)
{
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	else
		return (-1);
}
