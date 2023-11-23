/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:26:43 by smallem           #+#    #+#             */
/*   Updated: 2023/11/23 12:09:10 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigquit_handler(int signo, t_term *term)
{
	(void)signo;
	(void)term;
}

void	sigint_handler(int signo, t_term *term)
{
	(void)signo;
	(void)term;
}

void	sigstp_handler(int signo, t_term *term)
{
	(void)signo;
	(void)term;
}
