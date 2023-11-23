/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:00:41 by smallem           #+#    #+#             */
/*   Updated: 2023/11/23 17:41:11 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_term *term, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (term->env[++i])
		printf("%s\n", term->env[i]);
	term->ex_stat = 0;
}

void	ft_pwd(t_term *term, t_cmd *cmd)
{
	int		i;
	char	cwd[1024];

	i = 0;
	while (term->env[i])
	{
		if (!ft_strncmp(term->env[i], "PWD=", ft_strlen("PWD=")))
		{
			printf("%s\n", ft_strchr(term->env[i], '/'));
			break ;
		}
		i++;
	}
	if (!term->env[i])
	{
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
	}
	term->ex_stat = 0;
}

void	ft_exit(t_term *term, t_cmd *cmd)
{
	exit(term->ex_stat);
}
