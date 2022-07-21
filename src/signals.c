/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:50:52 by gborne            #+#    #+#             */
/*   Updated: 2022/07/17 02:50:56 by gborne           ###   ########.fr       */
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
