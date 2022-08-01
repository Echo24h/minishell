/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:50:52 by gborne            #+#    #+#             */
/*   Updated: 2022/08/01 18:18:36 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	control_c(void)
{
	pid_t	pid;
	int		is_kill;

	pid = wait(NULL);
	is_kill = 0;
	while (pid > 0)
	{
		kill(pid, SIGTERM);
		is_kill++;
		pid = wait(NULL);
	}
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (is_kill == 0)
		rl_redisplay();
}

void	signal_controller(int signal)
{
	if (signal == SIGINT)
		control_c();
}
