/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/05/27 20:48:23 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin(t_cmd *cmd, int	*fd)
{
	//ft_printf("size: %d, cmd: '%s'", ft_strlen(cmd->cmd), cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		echo(cmd, fd);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		env(cmd, fd);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		pwd(cmd, fd);
	else
		write(fd[1], cmd->cmd, ft_strlen(cmd->cmd) + 1);
	return (0);
}

