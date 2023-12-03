/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:26:43 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 19:16:39 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	termios_echoback(bool echo_ctl_chr)
{
	struct termios	terminos_p;
	int				status;

	(void)echo_ctl_chr;
	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
}

void	sighp(int signo)
{
	if (signo == SIGINT)
		return ;
}

void	hsig_int(int signo)
{
	if (signo == SIGINT)
		g_signo = 2;
}

void	sighandler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
