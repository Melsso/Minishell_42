/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:56:41 by smallem           #+#    #+#             */
/*   Updated: 2023/09/05 16:42:27 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_env(char **env)
{
	ssize_t	len;
	char	**new_ev;

	len = 0;
	while (env[len])
		len++;
	new_ev = (char **)malloc(sizeof(char *) * (len + 1));	
	if (!new_ev)
	{
		//malloc error
	}
	len = -1;
	while (env[++len])
		new_ev[len] = ft_strdup(env[len]);
	new_ev[len] = NULL;
	return (new_ev);
}

// char	*get_cmd_path(char **env, char *cmd)
// {
// 	char	*tmp;
// 	ssize_t	i;

// 	i = -1;
// 	while (env[++i])
// 	{
// 		if (!ft_strncmp(env[i], "PATH=", ft_strlen(env[i])))
// 			break ;
// 	}
// 	if (!env[i])
// 		return (NULL);
// }
