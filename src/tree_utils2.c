/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:56:41 by smallem           #+#    #+#             */
/*   Updated: 2023/10/26 15:25:58 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_env(char **env, t_term *term)
{
	ssize_t	len;
	char	**new_ev;

	len = 0;
	while (env[len])
		len++;
	new_ev = (char **)my_malloc(&term->mem_lst, sizeof(char *) * (len + 1));	
	len = -1;
	while (env[++len])
		new_ev[len] = ft_strdup(env[len], term);
	new_ev[len] = NULL;
	return (new_ev);
}

char	*get_path(t_term *term, char *cmd)
{
	int	i;
	char	*path;
	char	*line;
	char	**ppath;

	i = -1;
	path = NULL;
	while (term->env[++i])
	{
		if (!ft_strncmp(term->env[i], "PATH=", ft_strlen("PATH=")))
		{
			path = ft_strdup(term->env[i], term);
			break ;
		}
	}
	if (!path)
		return (NULL);
	ppath = ft_split(path, ':', term);
	i = -1;
	while (ppath[++i])
	{
		line = ft_strjoin(ft_strjoin(ppath[i], "/", term), cmd, term);
		if (access(line, X_OK | F_OK) == 0)
			return (line);
	}
	return (NULL);
}

static int	open_file(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
	{
		if (!ft_strncmp(cmd->args[i], ">", ft_strlen(cmd->args[i])) || !ft_strncmp(cmd->args[i], ">>", ft_strlen(cmd->args[i])))
		{
			cmd->fd_out = open(cmd->args[i + 1], O_CREAT | O_APPEND | O_WRONLY);
			if (cmd->fd_out < 0)
				return (printf("%s: no such file or directory\n", cmd->args[i + 1]), 0);
		}
		else if (!ft_strncmp(cmd->args[i], "<", ft_strlen(cmd->args[i])))
		{
			cmd->fd_in = open(cmd->args[i + 1], O_RDONLY);
			if (cmd->fd_in < 0)
				return (printf("%s: no such file or directory\n", cmd->args[i + 1]), 0);
		}
	}
	return (1);
}

t_cmd	*build_cmd(t_term *term, t_tree **node, int *ind)
{
	t_cmd	*cmd;
	char	*tmp;
	char	*cmd_name;
	int		i;

	cmd = (t_cmd *)my_malloc(&term->mem_lst, sizeof(t_cmd));
	tmp = NULL;
	if ((*node)->content)
	{
		tmp = (char *)(*node)->content;
		cmd->args = splt_space(tmp, term);
		cmd->fd_in = 0;
		cmd->fd_out = 1;
		cmd->index = *ind;
		if (!open_file(cmd))
			return (NULL);
		if (!ft_strncmp(cmd->args[0], ">", ft_strlen(cmd->args[0]))
			|| !ft_strncmp(cmd->args[0], "<", ft_strlen(cmd->args[0])))
			i = 2;
		else
			i = 0;
		cmd_name = ft_strdup(cmd->args[i], term);
		cmd->path = get_path(term, cmd_name);
		if (!cmd->path)
			return (printf("%s: command not found\n", cmd_name), NULL);
		return (cmd);
	}
	return (NULL);
}
