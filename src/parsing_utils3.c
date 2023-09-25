/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:54:27 by smallem           #+#    #+#             */
/*   Updated: 2023/09/25 13:12:55 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_charset(char c)
{
	if (c == TK_PIPE || c == ';' || c == '&')
		return (1);
	else
		return (0);
}

int	check_syntax(char *input)
{
	int		i;
	char	c;

	if (check_charset(input[0]))
	{
		printf("syntax error near unexpected token '%c'\n", input[0]);
		return (0);
	}
	i = -1;
	while (input[++i])
	{
		if (input[i] == TK_SQUOTE || input[i] == TK_DQUOTE)
		{
			c = input[i++];
			while (input[i] && input[i] != c)
				i++;
			if (input[i] == c)
				continue;
		}
		else if ((input[i] == TK_GREATER || input[i] == TK_LESS) && !input[i + 1])
		{
			printf("syntax error near unexpected token 'newline'\n");
			return (0);
		}	
	}
	return (1);
}

int	last_pipe(t_term *term)
{
	int	i;

	i = -1;
	while (term->input[++i])
	{
		if (term->input[i] == TK_PIPE)
		{
			i++;
			if (!term->input[i])
				return (1);
			while (term->input[i] && (term->input[i] == TK_SPACE
				|| term->input[i] == TK_TAB || term->input[i] == TK_NL))
				i++;
			if (!term->input[i])
				return (1);
		}
	}
	return (0);
}

int	check_buff(t_term *term)
{
	int	i;
	char	c;

	i = -1;
	while (term->input[++i])
	{
		if (term->input[i] == TK_SQUOTE || term->input[i] == TK_DQUOTE)
		{
			c = term->input[i++];
			while (term->input[i] && term->input[i] != c)
				i++;
			if (term->input[i] == c)
				continue ;
			else
			{
				if (c == TK_SQUOTE)
					return (1);
				else if (c == TK_DQUOTE)
					return (2);
			}
		}
		if (term->input[i] == TK_PIPE && !term->input[i + 1])
			return (3);
		else if (term->input[i] == TK_PIPE && term->input[i + 1] == TK_SQUOTE && !term->input[i + 2])
			return (4);
		else if (term->input[i] == TK_PIPE && term->input[i + 1] == TK_DQUOTE && !term->input[i + 2])
			return (5);
	}
	return (0);
}

static char	*update_rl(int flag, t_term *term, char *t)
{
	char	*tmp;

	tmp = NULL;
	if (flag == 1)
	{
		if (t && !ft_strncmp(t, "pipe quote>", ft_strlen(t)))
			tmp = ft_strdup("pipe quote>", term);
		else
			tmp = ft_strdup("quote>", term);
	}
	else if (flag == 2)
	{
		if (t && !ft_strncmp(t, "pipe dquote>", ft_strlen(t)))
			tmp = ft_strdup("pipe dquote>", term);
		else
			tmp = ft_strdup("dquote>", term);
	}
	else if (flag == 3)
		tmp = ft_strdup("pipe>", term);
	else if (flag == 4)
		tmp = ft_strdup("pipe quote>", term);
	else if (flag == 5)
		tmp = ft_strdup("pipe dquote>", term);
	return (tmp);
}

void	read_more(t_term *term, int flag)
{
	char	*tmp;
	char	*nl;

	tmp = update_rl(flag, term, NULL);
	while (flag)
	{
		term->input = ft_strjoin(term->input, "\n", term);
		nl = readline(tmp);
		term->input = ft_strjoin(term->input, nl, term);
		free(nl);
		nl = NULL;
		flag = check_buff(term);
		tmp = update_rl(flag, term, tmp);
	}
}

void	check_incomplete(char *input, t_term *term)
{
	int	flag;

	term->input = ft_strdup(input, term);
	flag = check_buff(term);
	if (flag > 0)
		read_more(term, flag);
	return ;
}

int check_input(char *input, t_term *term)
{
	if (!check_syntax(input))
		return (0);
	check_incomplete(input, term);
	return (check_syntax(term->input));
}
