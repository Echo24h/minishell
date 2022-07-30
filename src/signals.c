/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:50:52 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 20:29:21 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	control_c(void)
{
	write(1, "\n", 1);
	rl_redisplay();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, CYELLOW "minishell$ " RESET,
		ft_strlen(CYELLOW "minishell$ " RESET));
}

void	signal_controller(int signal)
{
	if (signal == SIGINT)
		control_c();
}
