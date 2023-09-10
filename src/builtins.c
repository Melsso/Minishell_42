/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:00:41 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 14:44:35 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_term *term)
{
	size_t	i;

	i = -1;
	while (term->env[++i])
		printf("%s\n", term->env[i]);	
}

static void	update_ev(char *path, t_term *term)
{
	size_t	i;
	char	*fp;
	char	*tmp;
	char	cwd[1024];
	int		ind;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		fp = ft_strjoin("PWD=", cwd, term);
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], "PWD=", ft_strlen("PWD=")))
		{
			tmp = term->env[i];
			ind = i;
			break ;
		}
		i++;
	}
	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
			term->env[i] = ft_strjoin("OLDPWD=", tmp, term);
		i++;
	}
	term->env[ind] = ft_strjoin("PWD=", cwd, term);
}

void	ft_cd(t_term *term)
{
	char	**cmd;
	char	*path;
	int	len;

	len = -1;
	while (cmd[++len])
		;
	if (len == 1)
	{
		len = 0;
		while (term->env[len])
		{
			if (!ft_strncmp(term->env[len], "HOME=", ft_strlen("HOME=")))
			{
				path = ft_strdup(term->env[len][4], term);
				break ;
			}
			len++;
		}
		chdir(path);
	}
	else if (len == 2)
	{
		if (chdir(cmd[1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", cmd[1]);
		}
	}
	else
	{
		//too many args
	}
}

void	ft_pwd(t_term *term)
{
	size_t	i;
	char	*pwd;
	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], "PWD=", ft_strlen("PWD=")))
			printf("%s\n", ft_strchr(term->env[i], '/'));
		i++;
	}
}
