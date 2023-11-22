/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:12:58 by smallem           #+#    #+#             */
/*   Updated: 2023/11/22 17:14:38 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_outfiles(int flag, char *name, t_cmd *cmd)
{
	if (flag == 1 || flag == 3)
	{
		if (access(name, F_OK) == 0)
		{
			if (access(name, W_OK) == 0)
			{
				if (flag == 1)
					cmd->fd_out = open(name, O_WRONLY | O_TRUNC, 0644);
				else if (flag == 3)
					cmd->fd_out = open(name, O_WRONLY | O_APPEND, 0644);
			}
			else
			{
				ex_stat = 1;
				return (ft_putstr_fd(name, 1), ft_putstr_fd(": Permission denied\n", 1), -1);
			}
		}
		else
			cmd->fd_out = open(name, O_WRONLY | O_CREAT, 0644);
	}
	return (1);
}

int	open_infiles(int flag, char *name, t_cmd *cmd)
{
	if (flag == 2)
	{
		if (access(name, F_OK) == 0)
		{
			if (access(name, R_OK) == 0)
				cmd->fd_in = open(name, O_RDONLY);
			else
			{
				ex_stat = 1;
				return (ft_putstr_fd(name, 1), ft_putstr_fd(": Permission denied\n", 1), -1);
			}
		}
		else
		{
			ex_stat = 1;
			return (ft_putstr_fd(name, 1), ft_putstr_fd(": No such file or directory\n", 1), -1);
		}
	}
	return (1);
}
