/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/05/18 15:42:39 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		return (1);
	return (0);
}

int	builtin(t_cmd *cmd)
{
	//ft_printf("size: %d, cmd: '%s'", ft_strlen(cmd->cmd), cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		echo(cmd);
	else
		write(1, cmd->cmd, ft_strlen(cmd->cmd) + 1);
	return (0);
}

