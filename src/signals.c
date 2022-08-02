/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:50:52 by gborne            #+#    #+#             */
/*   Updated: 2022/08/02 02:48:15 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	edit_signal(int signal)
{
	free(g_status);
	g_status = ft_itoa(signal);
}

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
	else
	{
		free(g_status);
		g_status = ft_itoa(130);
	}
}

static void	control_slash(void)
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
	if (is_kill)
	{
		write(1, "Quit: 3\n", 9);
		rl_replace_line("", 0);
	}
	rl_on_new_line();
	if (is_kill == 0)
		rl_redisplay();
	else
	{
		free(g_status);
		g_status = ft_itoa(131);
	}
}

void	signal_controller(int signal)
{
	if (signal == SIGINT)
		control_c();
	if (signal == SIGQUIT)
		control_slash();
}
