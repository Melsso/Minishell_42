/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:36 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 19:03:33 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	output_args(t_cmd *cmd, int start, int nl_flag, t_term *term)
{
	while (cmd->args[start])
	{
		ft_putstr_fd(cmd->args[start], cmd->fd_out);
		start++;
		if (cmd->args[start])
			ft_putstr_fd(" ", cmd->fd_out);
	}
	if (nl_flag)
		ft_putstr_fd("\n", cmd->fd_out);
	term->ex_stat = 0;
}

void	ft_echo(t_term *term, t_cmd *cmd)
{
	int	i;
	int	start;
	int	nl_flag;

	nl_flag = 1;
	start = 1;
	while (cmd->args[start])
	{
		if (cmd->args[start][0] == '-' && cmd->args[start][1])
		{
			i = 1;
			while (cmd->args[start][i] && cmd->args[start][i] == 'n')
				i++;
			if (!cmd->args[start][i])
				nl_flag = 0;
			else
				break ;
		}
		else
			break ;
		start++;
	}
	output_args(cmd, start, nl_flag, term);
}
