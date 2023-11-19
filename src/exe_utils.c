/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:39 by smallem           #+#    #+#             */
/*   Updated: 2023/11/19 15:12:00 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_cmd(t_cmd *cmd, t_term *term)
{
	int		i;
	char	**mat;
	int		flag;

	i = 0;
	flag = 0;
	while (cmd->args[0][i])
	{
		if (cmd->args[0][i] == '/')
			break ;
		i++;
	}
	if (!cmd->args[0][i])
		cmd->path = get_path(term, cmd->args[0]);	
	else if (access(cmd->args[0], F_OK) == 0)
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
			flag = 2;
		}
	}
	else
	{
		cmd->path = NULL;
		flag = 1;
	}
	if (!cmd->path && !flag)
		printf("%s: command not found\n", cmd->args[0]);
	if (!cmd->path && flag == 1)
		printf("%s: No such file or directory\n", cmd->args[0]);
	if (!cmd->path && flag == 2)
		printf("%s: Permission denied\n", cmd->args[0]);
}

static void	exe_builtins(t_cmd *cmd, t_term *term)
{
	if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "export", ft_strlen("export")))
		{
			ft_export(term, cmd);
			exit(ex_stat);
		}
	else if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "env", ft_strlen("env")))
	{
		ft_env(term, cmd);
		exit(ex_stat);
	}
	else if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")))
	{
		ft_echo(term, cmd);
		exit(ex_stat);
	}
	else if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "unset", ft_strlen("unset")))
	{
		ft_unset(term, cmd);
		exit(ex_stat);
	}
	else if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "cd", ft_strlen("cd")))
	{
		ft_cd(term, cmd);
		exit(ex_stat);
	}
	else if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd")))
	{
		ft_pwd(term, cmd);
		exit(ex_stat);
	}
	else if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0]))
		&& !ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")))
		ft_exit(term, cmd);
}

int exec_cmd(t_cmd *cmd, int tmp, t_term *term)
{
	dup2(tmp, STDIN_FILENO);
	close(tmp); // check
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
	exe_builtins(cmd, term);
	check_cmd(cmd, term);
	if (execve(cmd->path, cmd->args, term->env) == -1)
	{
		ex_stat = errno;
		exit(errno);
	}	
	return (1);
}

int exec_tree(t_term *term, t_tree *tree, int *tmp, int *fd)
{
	t_cmd	*cmd;

	if (tree->type == TK_PL)
	{
		exec_tree(term, tree->l, tmp, fd);
		exec_tree(term, tree->r, tmp, fd);
	}
	else if (tree->type == TK_CMD)
	{
		cmd = (t_cmd *) tree->content;
		if (cmd->index == term->nb_pipes) // check
		{
			if (!fork())
			{
				exec_cmd(cmd, *tmp, term);
				return (1);
				// error
			}
			close(*tmp);
			while (waitpid(-1, NULL, WUNTRACED) != -1)
				;
			*tmp = dup(STDIN_FILENO);
		}
		else
		{
			pipe(fd);
			if (!fork())
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				exec_cmd(cmd, *tmp, term);
				return (1);
				// error
			}
			close(fd[1]);
			close(*tmp);
			*tmp = fd[0];
		}
	}
	return (0);
}

int execution(t_term *term)
{
	int tmp;
	int fd[2];

	tmp = dup(STDIN_FILENO);
	if (!term->ast)
		return 1;
	exec_tree(term, term->ast, &tmp, fd);
	close(tmp);
	return (0);
}
