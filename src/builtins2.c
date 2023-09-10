/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:11 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 14:45:20 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_ev(t_term *term, char *var)
{
	size_t	i;

	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], var, ft_strlen(var)))
		{
			while (term->env[i])
			{
				term->env[i] = term->env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

void	ft_unset(t_term *term)
{
	size_t	len;
	char	**cmd;

	len = 0;
	while (cmd[len])
		len++;
	if (len == 1)
	{
		printf("unset: not enough arguments\n");
	}
	else
	{
		len = 1;
		while (cmd[len])
		{
			update_ev(term, ft_strjoin(cmd[len], "=", term));
			len++;
		}
	}
}
