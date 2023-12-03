/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:27 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 19:03:41 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_2ev(t_term *term, char *line, int i)
{
	char	**new_ev;

	if (!term->env[i])
	{
		new_ev = (char **)my_malloc(&term->mem_lst, (i + 2) * sizeof(char *));
		i = -1;
		while (term->env[++i])
			new_ev[i] = ft_strdup(term->env[i], term);
		new_ev[i++] = ft_strdup(line, term);
		new_ev[i] = NULL;
		term->env = new_ev;
	}
}

static void	err_msg(char c, t_term *term)
{
	ft_putstr_fd("export: '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	term->ex_stat = 1;
	return ;
}

static char	*make_line(char *arg, t_term *term)
{
	char	*delim;
	char	*line;
	int		i;

	delim = ft_strchr(arg, '=');
	if (arg == delim)
		return (err_msg(*arg, term), NULL);
	if (delim)
		*delim++ = 0;
	if (ft_isalpha(arg[0]) || arg[0] == '_')
	{
		i = 1;
		while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
			i++;
		if (arg[i])
			return (err_msg(arg[i], term), NULL);
	}
	else
		return (err_msg(arg[0], term), NULL);
	line = ft_strjoin(ft_strjoin(arg, "=", term), delim, term);
	return (line);
}

static void	update_ev(t_term *term, char *arg)
{
	int		i;
	char	**mat;
	char	*line;

	i = 0;
	line = make_line(arg, term);
	if (!line)
		return ;
	while (term->env[i])
	{
		mat = ft_split(term->env[i], '=', term);
		if (!ft_strncmp(mat[0], arg, ft_strlen(arg))
			&& !ft_strncmp(mat[0], arg, ft_strlen(mat[0])))
		{
			term->env[i] = line;
			break ;
		}
		i++;
	}
	add_2ev(term, line, i);
}

void	ft_export(t_term *term, t_cmd *cmd)
{
	int	len;

	len = 0;
	while (cmd->args[len])
		len++;
	if (len == 1)
	{
		len = -1;
		while (term->env[++len])
			printf("declare -x %s\n", term->env[len]);
		term->ex_stat = 0;
	}
	else
	{
		len = 1;
		while (cmd->args[len])
		{
			update_ev(term, cmd->args[len]);
			len++;
		}
	}
}
