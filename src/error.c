/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:24:38 by smallem           #+#    #+#             */
/*   Updated: 2023/11/28 16:41:28 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_perm(t_cmd *cmd, t_term *term, int i)
{
	char	**mat;

	if (access(cmd->args[0], F_OK) == 0)
	{
		if (access(cmd->args[0], X_OK) == 0)
		{
			cmd->path = cmd->args[0];
			mat = ft_split(cmd->args[0], '/', term);
			i = 0;
			while (mat[i + 1])
				i++;
			cmd->args[0] = mat[i];
		}
		else
		{
			cmd->path = NULL;
			return (2);
		}
	}
	else
	{
		cmd->path = NULL;
		return (1);
	}
	return (0);
}

static int	ft_err(int flag, t_cmd *cmd, t_term *term)
{
	if (!cmd->path)
	{
		if (flag == 0)
			ft_error(cmd->args[0], ": command not found", term, 127);
		if (flag == 1)
			ft_error(cmd->args[0], ": No such file or directory", term, 127);
		if (flag == 2)
			ft_error(cmd->args[0], ": Permission denied", term, 126);
		return (0);
	}
	else
		return (1);
}

int	check_cmd(t_cmd *cmd, t_term *term)
{
	int		i;
	int		flag;

	i = 0;
	while (cmd->args[0][i])
	{
		if (cmd->args[0][i] == '/')
			break ;
		i++;
	}
	flag = 0;
	if (!cmd->args[0][i])
		cmd->path = get_path(term, cmd->args[0]);
	else
		flag = check_perm(cmd, term, i);
	if (is_builtin(cmd))
		return (1);
	if (!ft_err(flag, cmd, term))
		return (0);
	return (1);
}

void	ft_error(char *msg, char *ptr, t_term *term, int val)
{
	ft_putstr_fd(msg, 2);
	if (ptr)
	{
		ft_putstr_fd(ptr, 2);
		ft_putstr_fd("\n", 2);
	}
	term->ex_stat = val;
}

void	ft_print_err(char *ptr, int val, t_term *term)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(ptr, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	term->ex_stat = val;
}
