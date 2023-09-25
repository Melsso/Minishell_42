/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:54:27 by smallem           #+#    #+#             */
/*   Updated: 2023/09/25 18:35:05 by smallem          ###   ########.fr       */
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
	
	i = 0;
	while (input[i] && (input[i] == TK_SPACE || input[i] == TK_TAB))
		i++;
	if (check_charset(input[i]))
	{
		printf("syntax error near unexpected token '%c'\n", input[0]);
		return (0);
	}
	while (input[i])
	{
		if (input[i] == TK_SQUOTE || input[i] == TK_DQUOTE)
		{
			c = input[i++];
			while (input[i] && input[i] != c)
				i++;
			if (input[i] == c)
			{
				i++;
				continue;
			}	
		}
		else if ((input[i] == TK_GREATER || input[i] == TK_LESS))
		{
			i++;
			while (input[i] && (input[i] == TK_SPACE || input[i] == TK_TAB))
				i++;
			if (!input[i])
			{
				printf("syntax error near unexpected token 'newline'\n");
				return (0);	
			}
		}
		else if (input[i] == TK_PIPE && input[i + 1] == TK_PIPE)
		{
			printf("syntax error near unexpected token '|'\n");
			return (0);	
		}
		i++;
	}
	return (1);
}

int	check_afterpipe(t_term *term, int i, int flag)
{
	char	c;

	while (term->input[i] && (term->input[i] == TK_SPACE || term->input[i] == TK_TAB || term->input[i] == TK_NL))
		i++;
	if (!term->input[i])
		return (flag);
	while (term->input[i])
	{
		if (term->input[i] == TK_SQUOTE || term->input[i] == TK_DQUOTE)
		{
			c = term->input[i++];
			while (term->input[i] && term->input[i] != c)
				i++;
			if (term->input[i] == c)
			{
				i++;
				continue ;
			}
			else
			{
				if (c == TK_SQUOTE)
					return (flag + 1);
				else
					return (flag + 2);
			}
		}
		i++;
	}
	return (0);
}

int	check_buff(t_term *term)
{
	int	i;
	int	flag;
	char	c;

	i = 0;
	while (term->input[i])
	{
		if (term->input[i] == TK_PIPE)
		{
			i++;
			if (term->input[i] == TK_PIPE)
				return (-1);
			flag = check_afterpipe(term, i, 3);
			if (flag)
				return (flag);
		}
		if (term->input[i] == TK_SQUOTE || term->input[i] == TK_DQUOTE)
		{
			c = term->input[i++];
			while (term->input[i] && term->input[i] != c)
				i++;
			if (term->input[i] == c)
			{
				i++;
				continue ;
			}
			else
			{
				if (c == TK_SQUOTE)
					return (1);
				else
					return (2);
			}
		}
		i++;
	}
	return (0);
}

static char	*update_rl(int flag, t_term *term)
{
	char	*tmp;

	tmp = NULL;
	if (flag == 1)
		tmp = ft_strdup("quote>", term);
	else if (flag == 2)
		tmp = ft_strdup("dquote>", term);
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

	tmp = update_rl(flag, term);
	while (flag)
	{
		term->input = ft_strjoin(term->input, "\n", term);
		nl = readline(tmp);
		term->input = ft_strjoin(term->input, nl, term);
		free(nl);
		nl = NULL;
		flag = check_buff(term);
		if (flag == -1)
			break ;
		tmp = update_rl(flag, term);
	}
}

void	check_incomplete(t_term *term)
{
	int	flag;

	flag = check_buff(term);
	if (flag > 0)
		read_more(term, flag);
	return ;
}

int check_input(char *input, t_term *term)
{
	term->input = ft_strdup(input, term);
	free(input);
	input = NULL;
	if (!check_syntax(term->input))
		return (0);
	check_incomplete(term);
	return (check_syntax(term->input));
}
