/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:43:46 by smallem           #+#    #+#             */
/*   Updated: 2023/11/23 17:42:06 by smallem          ###   ########.fr       */
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

static int	check_perm(t_cmd *cmd, t_term *term, int i)
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

static void	check_cmd(t_cmd *cmd, t_term *term)
{
	int		i;
	char	**mat;
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
	if (!cmd->path && !flag)
		printf("%s: command not found\n", cmd->args[0]);
	if (!cmd->path && flag == 1)
		printf("%s: No such file or directory\n", cmd->args[0]);
	if (!cmd->path && flag == 2)
		printf("%s: Permission denied\n", cmd->args[0]);
}

int	exec_cmd(t_cmd *cmd, int tmp, t_term *term)
{
	dup2(tmp, STDIN_FILENO);
	close(tmp);
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
	exe_builtins(cmd, term, 1);
	check_cmd(cmd, term);
	if (execve(cmd->path, cmd->args, term->env) == -1)
	{
		term->ex_stat = errno;
		exit(errno);
	}
	return (1);
}
