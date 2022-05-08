/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:12:01 by mbastard          #+#    #+#             */
/*   Updated: 2022/05/04 14:21:37 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	control_c()
{

}

static void	control_slash()
{

}

static void	control_z()
{

}

void	signal_controller(int signal)
{
	if (signal == SIGINT)
		control_c();
	else if (signal == SIGQUIT)
		control_slash();
	else if (signal == SIGTSTP)
		control_z();
}
