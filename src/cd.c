/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:00:51 by smallem           #+#    #+#             */
/*   Updated: 2023/11/17 16:55:00 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(t_term *term, t_cmd *cmd)
{
	char	*path;
	char	ocwd[1024];
	char	cwd[1024];
	int		len;
	int		i;

	len = -1;
	while (cmd->args[++len])
		;
	getcwd(ocwd, sizeof(ocwd));
	if (len == 1)
	{
		len = 0;
		while (term->env[len])
		{
			if (!ft_strncmp(term->env[len], "HOME=", ft_strlen("HOME=")))
			{
				path = ft_strdup(term->env[len][5], term);
				break ;
			}
			len++;
		}
		if (!term->env[len])
		{
			printf("cd: HOME not set\n");
			ex_stat = 1;
			return ;
		}
		chdir(path);
	}
	else
	{
		if (chdir(cmd->args[1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", cmd[1]);
			ex_stat = 1;
			return ;
		}
	}
	getcwd(cwd, sizeof(cwd));
	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], "PWD=", ft_strlen("PWD=")))
			term->env[i++] = ft_strjoin("PWD=", cwd, term);
		else if (!ft_strncmp(term->env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
			term->env[i++] = ft_strjoin("OLDPWD=", ocwd, term);
		else
			i++;
	}
	ex_stat = 0;
}
