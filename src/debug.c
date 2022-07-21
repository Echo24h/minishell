/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:15:36 by gborne            #+#    #+#             */
/*   Updated: 2022/05/27 19:15:32 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_cmd(t_cmd *cmd)
{
	int	i;
	write(1, "----\n", 6);
	write(1, "cmd->cmd : ", 12);
	write(1, cmd->cmd, ft_strlen(cmd->cmd));
	write(1, "\n", 2);
	write(1, "cmd->arg : ", 12);
	i = 0;
	while (cmd->arg[i])
	{
		ft_putnbr(i);
		write(1, cmd->arg[i], ft_strlen(cmd->arg[i]));
		write(1, "-", 2);
		i++;
	}
	write(1, "\n", 2);
	write(1, "----\n", 6);
}
