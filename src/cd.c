/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:00:51 by smallem           #+#    #+#             */
/*   Updated: 2023/11/23 17:41:23 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_env(char *ocwd, t_term *term)
{
	char	cwd[1024];
	int		i;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], "PWD=", ft_strlen("PWD=")))
			term->env[i++] = ft_strjoin("PWD=", cwd, term);
		else if (!ft_strncmp(term->env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
			term->env[i++] = ft_strjoin("OLDPWD=", ocwd, term);
		else
			i++;
	}
}

static void	move_home(t_term *term)
{
	int		i;
	char	*path;

	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], "HOME=", ft_strlen("HOME=")))
		{
			path = ft_strdup(&term->env[i][5], term);
			break ;
		}
		i++;
	}
	if (!term->env[i])
	{
		printf("cd: HOME not set\n");
		term->ex_stat = 1;
		return ;
	}
	chdir(path);
}

void	ft_cd(t_term *term, t_cmd *cmd)
{
	char	ocwd[1024];
	int		len;

	len = -1;
	while (cmd->args[++len])
		;
	getcwd(ocwd, sizeof(ocwd));
	if (len == 1)
		move_home(term);
	else
	{
		if (chdir(cmd->args[1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", cmd->args[1]);
			term->ex_stat = 1;
			return ;
		}
	}
	update_env(ocwd, term);
	term->ex_stat = 0;
}
