/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:43:46 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 19:17:06 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "export", ft_strlen("export")))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "env", ft_strlen("env")))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "unset", ft_strlen("unset")))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd")))
		return (1);
	else if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")))
		return (1);
	return (0);
}

void	exe_builtins(t_cmd *cmd, t_term *term, int flag)
{
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "export", ft_strlen("export")))
		ft_export(term, cmd);
	else if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "env", ft_strlen("env")))
		ft_env(term, cmd);
	else if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")))
		ft_echo(term, cmd);
	else if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "unset", ft_strlen("unset")))
		ft_unset(term, cmd);
	else if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "cd", ft_strlen("cd")))
		ft_cd(term, cmd);
	else if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd")))
		ft_pwd(term, cmd);
	else if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")))
		ft_exit(term, cmd);
	if (flag && is_builtin(cmd))
		exit(term->ex_stat);
	return ;
}

int	exec_cmd(t_cmd *cmd, int tmp, t_term *term)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	exe_builtins(cmd, term, 1);
	if (cmd->fd_in > 2)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 2)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	if (execve(cmd->path, cmd->args, term->env) == -1)
	{
		term->ex_stat = errno;
		exit(term->ex_stat);
	}
	return (1);
}
