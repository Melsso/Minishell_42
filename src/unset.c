/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:11 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 19:04:02 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_ev(t_term *term, char *var)
{
	size_t	i;
	char	**mat;

	i = 0;
	while (term->env[i])
	{
		mat = ft_split(term->env[i], '=', term);
		if (!ft_strncmp(mat[0], var, ft_strlen(var))
			&& !ft_strncmp(mat[0], var, ft_strlen(mat[0])))
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
		term->ex_stat = 0;
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
		term->ex_stat = 0;
	}
}
