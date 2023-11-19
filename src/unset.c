/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:11 by smallem           #+#    #+#             */
/*   Updated: 2023/11/19 15:09:38 by smallem          ###   ########.fr       */
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

void	ft_unset(t_term *term, t_cmd *cmd)
{
	size_t	len;

	len = 0;
	while (cmd->args[len])
		len++;
	if (len == 1)
	{
		ex_stat = 0;
		return ;
	}
	else
	{
		len = 1;
		while (cmd->args[len])
		{
			update_ev(term, cmd->args[len]);
			len++;
		}
		ex_stat = 0;
	}
}
