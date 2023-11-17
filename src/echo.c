/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:36 by smallem           #+#    #+#             */
/*   Updated: 2023/11/17 17:06:01 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_term *term, t_cmd *cmd)
{
	int	i;
	int	start;
	int	nl_flag;

	nl_flag = 1;
	start = 1;
	if (cmd->args[1][0] == '-' && cmd->args[1][1])
	{
		i = 1;
		while (cmd->args[1][i] && cmd->args[1][i] == 'n')
			i++;
		if (!cmd->args[1][i])
		{
			nl_flag = 0;
			start = 2;
		}
	}
	while (cmd->args[start])
	{
		printf("%s", cmd->args[start]);
		start++;
		if (cmd->args[start])
			printf(" ");
	}
	if (nl_flag)
		printf("\n");
	ex_stat = 0;
	return ;
}
