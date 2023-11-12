/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:56:41 by smallem           #+#    #+#             */
/*   Updated: 2023/11/12 19:11:49 by smallem          ###   ########.fr       */
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

static void	check_rd(char **args, int *red)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		red[i] = 0;
		while (args[i][j])
		{
			if (args[i][j] == TK_SQUOTE || args[i][j] == TK_DQUOTE)
				j = skip_quote(args[i], j, args[i][j]);
			else if (args[i][j] == '>' || args[i][j] == '<')
			{
				red[i] = 1;
				break ;
			}
			j++;
		}
		i++;
	}
}

t_cmd	*build_cmd(t_term *term, t_tree **node, int *ind)
{
	t_cmd	*cmd;
	char	*tmp;
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
		i = 0;
		while (cmd->args[i])
			i++;
		cmd->red = (int *)my_malloc(&term->mem_lst, sizeof(int) * i);
		check_rd(cmd->args, cmd->red);
		return (cmd);
	}
	return (NULL);
}
