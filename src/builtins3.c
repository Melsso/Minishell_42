/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:27 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 14:45:56 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i + 1] && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}
static	size_t	check_present(char *arg, t_term *term)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		i++;
	}
	len = 0;
	while (term->env[len])
	{
		if (!ft_strncmp(term->env[len], arg, i - 1))
			return (len);
		len++;
	}
	return (0);
}

static void	update_ev(t_term *term, char *arg)
{
	size_t	len;
	char	**new_ev;

	if (!check_arg(arg))
	{
		// prolly change exit status;
		return ;
	}
	len = check_present(arg, term);
	if (!len)
	{
		while (term->env[len])
			len++;
		new_ev = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (len + 1));
		if (!new_ev)
		{
			//malloc erorr
		}
		len = 0;
		while (term->env[len])
			new_ev[len] = ft_strdup(term->env[len++], term);
		new_ev[len++] = ft_strdup(arg, term);
		new_ev[len] = NULL;
		term->env = new_ev;
	}
	else
		term->env[len] = ft_strdup(arg, term);
}

void	ft_export(t_term *term)
{
	char	**cmd;
	size_t	len;

	len = 0;
	while (cmd[len])
		len++;
	if (len == 1)
		ft_env(term);
	else
	{
		len = 0;
		while (cmd[len])
		{
			update_ev(term, cmd[len]);
			len++;
		}
	}
}
