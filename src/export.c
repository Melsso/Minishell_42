/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:27 by smallem           #+#    #+#             */
/*   Updated: 2023/11/19 15:01:53 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static void	update_ev(t_term *term, char *arg)
{
	int	i;
	char	*line;
	char	**new_ev;
	char	**name;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		else
			i++;
	}
	if (!arg[i])
		line = ft_strjoin(arg, "=", term);
	else
		line = ft_strdup(arg, term);
	name = ft_split(line, '=', term);
	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], name[0], ft_strlen(name[0])))
		{
			term->env[i] = line;
			break ;
		}
		else
			i++;
	}
	if (!term->env[i])
	{
		new_ev = (char **)my_malloc(&term->mem_lst, (i + 1) * sizeof(char *));
		i = 0;
		while (term->env[i])
		{
			new_ev[i] = ft_strdup(term->env[i], term);
			i++;
		}
		new_ev[i++] = ft_strdup(line, term);
		new_ev[i] = NULL;
		term->env = new_ev;
	}
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
		len = 0;
		while (cmd->args[len])
		{
			update_ev(term, cmd->args[len]);
			len++;
		}
	}
}
