/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:00:41 by smallem           #+#    #+#             */
/*   Updated: 2023/11/28 13:02:10 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_term *term, t_cmd *cmd)
{
	int		i;
	char	**mat;

	i = -1;
	(void)cmd;
	while (term->env[++i])
	{
		mat = ft_split(term->env[i], '=', term);
		if (mat[1])
			printf("%s\n", term->env[i]);
	}
	term->ex_stat = 0;
}

void	ft_pwd(t_term *term, t_cmd *cmd)
{
	int		i;
	char	cwd[1024];

	i = 0;
	(void)cmd;
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

static double	ft_atd(char *nptr)
{
	double			nb;
	unsigned int	i;
	int				sign;

	i = 0;
	nb = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= (-1);
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (nb * 10) + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

static void	check(t_term *term, t_cmd *cmd, int len)
{
	double	d;

	len = 0;
	if (cmd->args[1][len] == '-')
		len++;
	while (cmd->args[1][len] && cmd->args[1][len] >= '0'
		&& cmd->args[1][len] <= '9')
		len++;
	if (cmd->args[1][len])
		ft_print_err(cmd->args[1], 255, term);
	else
	{
		d = ft_atd(cmd->args[1]);
		len = ft_strlen(cmd->args[1]) - (d < 0);
		if (len > 19)
			ft_print_err(cmd->args[1], 255, term);
		else
			term->ex_stat = (char)d;
	}
}

void	ft_exit(t_term *term, t_cmd *cmd)
{
	int		len;

	len = 0;
	while (cmd->args[len])
		len++;
	if (len > 2)
	{
		ft_error("exit: too many arguments\n", NULL, term, 1);
		term->ex_stat = 1;
		return ;
	}
	else if (len == 1)
	{
		free_lst(&term->mem_lst);
		exit(term->ex_stat);
	}
	else
	{
		check(term, cmd, len);
		free_lst(&term->mem_lst);
		exit((char)term->ex_stat);
	}
}
