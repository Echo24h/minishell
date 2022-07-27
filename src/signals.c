/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:50:52 by gborne            #+#    #+#             */
/*   Updated: 2022/07/27 14:19:25 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	control_c()
{
	/*pid_t pid;

	pid = wait(NULL);
	while (pid > 0)
	{
		kill(pid, SIGTERM);
		printf("kill %d\n", pid);
		pid = wait(NULL);
	}*/
	//write( 1, PROMPT, ft_strlen(PROMPT));
	//rl_clear_history();
	//printf(" g_pid=%d\n", g_pid);
	write(1, "\n", 1);
	rl_redisplay();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, PROMPT, ft_strlen(PROMPT));
	//rl_redisplay();
	//rl_on_new_line();
	//rl_redisplay();
	//rl_redisplay();
}

void	signal_controller(int signal)
{
	if (signal == SIGINT)
		control_c();
}
