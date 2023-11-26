/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:52:47 by smallem           #+#    #+#             */
/*   Updated: 2023/11/26 14:15:23 by smallem          ###   ########.fr       */
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

static char	*find_path(t_term *term)
{
	char	*path;
	int		i;

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
	return (path);
}

char	*get_path(t_term *term, char *cmd)
{
	int		i;
	char	*path;
	char	*line;
	char	**ppath;

	path = find_path(term);
	if (!path)
		return (NULL);
	ppath = ft_split(path, ':', term);
	i = -1;
	while (ppath[++i])
	{
		line = ft_strjoin(ft_strjoin(ppath[i], "/", term), cmd, term);
		if (access(line, F_OK) == 0 && access(line, X_OK) == 0)
			return (line);
	}
	return (NULL);
}

int	is_space(char c)
{
	if (c == TK_SPACE || c == TK_TAB || c == TK_NL)
		return (1);
	return (0);
}

void	init_arr(int *arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
		arr[i++] = 0;
}
