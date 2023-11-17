/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:58:39 by smallem           #+#    #+#             */
/*   Updated: 2023/11/17 13:04:12 by smallem          ###   ########.fr       */
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
	check_cmd(cmd, term);
	if (execve(cmd->path, cmd->args, term->env) == -1)
	{
		ex_stat = errno;
		exit(errno);
	}
	return (1);
	// error
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

// static void	fix_args(t_cmd *cmd, t_term *term)
// {
// 	int		size;
// 	int		i;
// 	char	**args;

// 	i = 0;
// 	size = 0;
// 	while (cmd->args[i])
// 	{
// 		if ((!ft_strncmp(cmd->args[i], ">", ft_strlen(cmd->args[i]))
// 		|| !ft_strncmp(cmd->args[i], ">>", ft_strlen(cmd->args[i]))
// 		|| !ft_strncmp(cmd->args[i], "<", ft_strlen(cmd->args[i]))
// 		|| !ft_strncmp(cmd->args[i], "<<", ft_strlen(cmd->args[i]))) && cmd->red[i])
// 			size++;
// 		i++;
// 	}
	
// 	if (!size)
// 		return ;
// 	args = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (i - (size * 2)));
// 	size = 0;
// 	i = 0;
// 	while (cmd->args[i])
// 	{
// 		if ((!ft_strncmp(cmd->args[i], ">", ft_strlen(cmd->args[i]))
// 		|| !ft_strncmp(cmd->args[i], ">>", ft_strlen(cmd->args[i]))
// 		|| !ft_strncmp(cmd->args[i], "<", ft_strlen(cmd->args[i]))
// 		|| !ft_strncmp(cmd->args[i], "<<", ft_strlen(cmd->args[i]))) && cmd->red[i])
// 			i += 2;
// 		else
// 		{
// 			args[size] = ft_strdup(cmd->args[i], term);
// 			i++;
// 			size++;
// 		}
// 	}
// 	args[size] = NULL;
// 	cmd->args = args;
// }

// static void	open_file(t_cmd *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (cmd->args[++i])
// 	{
// 		if ((!ft_strncmp(cmd->args[i], ">", ft_strlen(cmd->args[i])) || !ft_strncmp(cmd->args[i], ">>", ft_strlen(cmd->args[i]))) && cmd->red[i])
// 		{
// 			if (!ft_strncmp(cmd->args[i], ">", ft_strlen(cmd->args[i])))
// 				cmd->fd_out = open(cmd->args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 			else
// 				cmd->fd_out = open(cmd->args[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
// 			if (cmd->fd_out < 0)
// 			{
// 				printf("%s: no such file or directory\n", cmd->args[i + 1]);
// 				ex_stat = errno;
// 			}
// 		}
// 		else if (!ft_strncmp(cmd->args[i], "<", ft_strlen(cmd->args[i])) && cmd->red[i])
// 		{
// 			cmd->fd_in = open(cmd->args[i + 1], O_RDONLY);
// 			if (cmd->fd_in < 0)
// 			{
// 				printf("%s: no such file or directory\n", cmd->args[i + 1]);
// 				ex_stat = errno;
// 			}
// 		}
// 	}
// }

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
