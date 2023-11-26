/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:27 by smallem           #+#    #+#             */
/*   Updated: 2023/11/26 14:29:51 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*fetch_l(t_term *term, char *arg, char ***name)
{
	char	*line;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		i++;
	}
	if (!arg[i])
		line = ft_strjoin(arg, "=", term);
	else
		line = ft_strdup(arg, term);
	*name = ft_split(line, '=', term);
	return (line);
}

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

static void	update_ev(t_term *term, char *arg)
{
	int		i;
	char	*line;
	char	**name;

	line = fetch_l(term, arg, &name);
	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], name[0], ft_strlen(name[0])))
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
		ft_env(term, cmd);
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
