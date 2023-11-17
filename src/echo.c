/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:24:36 by smallem           #+#    #+#             */
/*   Updated: 2023/11/17 17:28:19 by smallem          ###   ########.fr       */
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
	while (cmd->args[start])
	{
		if (cmd->args[start][0] == '-' && cmd->args[start][1])
		{
			i = 1;
			while (cmd->args[start][i] && cmd->args[start][i] == 'n')
				i++;
			if (!cmd->args[start][i])
				nl_flag = 0;
			else
				break ;
		}
		else
			break ;
		start++;
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
